#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <memory>
#include <string>
#include "WordSorter.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
    tcp::socket socket_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> req_;
    WordSorter wordSorter_;

public:
    explicit Session(tcp::socket socket);
    void run();

private:
    void do_read();
    void do_post();
    void do_write(http::response<http::string_body> res);
    http::response<http::string_body> handle_request();
};

class Listener : public std::enable_shared_from_this<Listener> {
    net::io_context& ioc_;
    tcp::acceptor acceptor_;

public:
    Listener(net::io_context& ioc, tcp::endpoint endpoint);

private:
    void do_accept();
};

class WebServer {
    net::io_context ioc_;
    std::shared_ptr<Listener> listener_;

public:
    WebServer(tcp::endpoint endpoint);
    void run();
};

#endif // WEBSERVER_H
