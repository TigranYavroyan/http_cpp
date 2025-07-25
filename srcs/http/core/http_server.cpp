#include <http_server.h>
#include <thread>
#include <handle_session.h>

HttpServer::HttpServer(int thread_count):
    ioc{thread_count},
    acceptor(ioc)
{}

void HttpServer::listen (unsigned short port, Callback cb) {
    tcp::endpoint endpoint (tcp::v4(), port);
    try {
        acceptor.open(endpoint.protocol());
        acceptor.set_option(boost::asio::socket_base::reuse_address(true));
        acceptor.bind(endpoint);
        acceptor.listen();
        cb();
        _do_accept();
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
        throw;
    }
}

void HttpServer::_do_accept() {
    try {
        while (true) {
            tcp::socket socket{ioc};
            acceptor.accept(socket);
            std::thread{handle_session, std::move(socket)}.detach();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}