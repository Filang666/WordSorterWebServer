#include "WebServer.h"

Session::Session(tcp::socket socket) : socket_(std::move(socket)) {}

void Session::run() {
    do_read();
}

http::response<http::string_body> Session::handle_request() {
    if (req_.method() == http::verb::get) {
        std::string html = R"(
        <!DOCTYPE html>
        <html>
        <head>
            <title>Word Sorter</title>
        </head>
        <body>
            <h1>Word Sorter</h1>
            <form method="post" action="/sort">
                <input name="words" type="text" placeholder="Enter words separated by spaces">
                <button type="submit">Sort Words</button>
            </form>
        </body>
        </html>
        )";
        http::response<http::string_body> res{http::status::ok, req_.version()};
        res.set(http::field::server, "Beast");
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req_.keep_alive());
        res.body() = html;
        res.prepare_payload();
        return res;
    }

    // For non-GET requests, return bad request
    http::response<http::string_body> res{http::status::bad_request, req_.version()};
    res.set(http::field::server, "Beast");
    res.set(http::field::content_type, "text/html");
    res.keep_alive(req_.keep_alive());
    res.prepare_payload();
    return res;
}

void Session::do_post() {
    std::string input = req_.body();
    wordSorter_.inputWords(input);
    wordSorter_.sortWords();

    std::string sortedWords = wordSorter_.displayWords();

    http::response<http::string_body> res{http::status::ok, req_.version()};
    res.set(http::field::server, "Beast");
    res.set(http::field::content_type, "text/plain");
    res.keep_alive(req_.keep_alive());
    res.body() = "Sorted Words: " + sortedWords;
    res.prepare_payload();

    do_write(std::move(res));
}

void Session::do_read() {
    auto self(shared_from_this());
    http::async_read(socket_, buffer_, req_,
        [this, self](beast::error_code ec, std::size_t bytes_transferred) {
            if (ec) {
                // Connection closed or error
                return;
            }

            if (req_.method() == http::verb::post) {
                do_post();
            } else {
                do_write(handle_request());
            }
        });
}

void Session::do_write(http::response<http::string_body> res) {
    auto self(shared_from_this());

    // Keep the response alive until async_write completes
    auto shared_res = std::make_shared<http::response<http::string_body>>(std::move(res));

    http::async_write(socket_, *shared_res,
        [this, self, shared_res](beast::error_code ec, std::size_t) {
            if (!ec) {
                // Gracefully close the connection
                beast::error_code shutdown_ec;
                socket_.shutdown(tcp::socket::shutdown_send, shutdown_ec);
            }
        });
}
Listener::Listener(net::io_context& ioc, tcp::endpoint endpoint)
    : ioc_(ioc), acceptor_(net::make_strand(ioc)) {
    beast::error_code ec;

    // Open the acceptor
    acceptor_.open(endpoint.protocol(), ec);
    if (ec) {
        std::cerr << "Open error: " << ec.message() << std::endl;
        return;
    }

    // Allow address reuse
    acceptor_.set_option(net::socket_base::reuse_address(true), ec);
    if (ec) {
        std::cerr << "Set option error: " << ec.message() << std::endl;
        return;
    }

    // Bind to the server address
    acceptor_.bind(endpoint, ec);
    if (ec) {
        std::cerr << "Bind error: " << ec.message() << std::endl;
        return;
    }

    // Start listening for connections
    acceptor_.listen(net::socket_base::max_listen_connections, ec);
    if (ec) {
        std::cerr << "Listen error: " << ec.message() << std::endl;
        return;
    }

    do_accept();
}

void Listener::do_accept() {
    acceptor_.async_accept(net::make_strand(ioc_), [this](beast::error_code ec, tcp::socket socket) {
        if (!ec) {
            std::make_shared<Session>(std::move(socket))->run();
        }
        do_accept();
    });
}

WebServer::WebServer(tcp::endpoint endpoint) {
    listener_ = std::make_shared<Listener>(ioc_, endpoint);
}

void WebServer::run() {
    ioc_.run();
}
