#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include <includes.h>

class HttpServer {
public:
    using Callback = std::function<void()>;

    HttpServer (const HttpServer&) = delete;
    HttpServer& operator= (const HttpServer&) = delete;

    HttpServer (int thread_count = 1);
    HttpServer(HttpServer&& other);
public:
    HttpServer& operator= (HttpServer&& other);
    void listen (unsigned short port, Callback cb);
private:
    void _do_accept();

    net::io_context ioc;
    tcp::acceptor acceptor;
};

#endif // HTTP_SERVER_HPP