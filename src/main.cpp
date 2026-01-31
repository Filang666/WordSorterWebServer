#include "WebServer.h"

int main() {
    tcp::endpoint endpoint(tcp::v4(), 8080);
    WebServer server(endpoint);
    server.run();
    return 0;
}
