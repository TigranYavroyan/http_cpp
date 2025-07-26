#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include <includes.h>
#include <request.h>
#include <response.h>
#include <router.h>
#include <type_traits>
#include <is_middleware.hpp>

class HttpServer {
public:
    using Callback = std::function<void()>;

    HttpServer (const HttpServer&) = delete;
    HttpServer& operator= (const HttpServer&) = delete;
    HttpServer (HttpServer&& other) = delete;
    HttpServer& operator= (HttpServer&& other) = delete;

    HttpServer (int thread_count = 1);
public:
    void listen (unsigned short port, Callback cb);

    void get(const std::string& path, Handler handler);
    void post(const std::string& path, Handler handler);
    void del(const std::string& path, Handler handler);
    void update(const std::string& path, Handler handler);
    void put(const std::string& path, Handler handler);
    void patch(const std::string& path, Handler handler);

    
    template <typename... Mids>
    std::enable_if_t<are_all_middlewares_v<Mids...>>
    use(Mids... ms) {
        (use(ms), ...);
    }

    void use(const std::string& path, Middleware middleware);
    void use(const std::string& path, MiddlewareFunc middleware);
    void use(Middleware middleware);
    void use(MiddlewareFunc middleware);
    void use(MiddlewareFuncPtr middleware);

    void print_routes () const;
private:
    void _do_accept();
    void _handle_session(tcp::socket socket);
    void _log_routing (int64_t ms, const Request& req, Response& res) const;

    net::io_context ioc_;
    tcp::acceptor acceptor_;
    Router router_;
};



#endif // HTTP_SERVER_HPP