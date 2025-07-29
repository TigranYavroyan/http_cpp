#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include <includes.h>
#include <request.h>
#include <response.h>
#include <router.hpp>
#include <type_traits>
#include <is_middleware.hpp>

namespace Karich {
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

        void use(const std::string& prefix, const Router& r);
        
        template <typename... Mids>
        std::enable_if_t<are_all_middlewares_v<Mids...>>
        use(Mids... ms);
    
        template <typename... Mids>
        std::enable_if_t<are_all_middlewares_v<Mids...>>
        use(const std::string& path, Mids... ms);

        template <typename Mid>
        std::enable_if_t<is_middleware_like_v<Mid>>
        use(Mid ms);
    
        template <typename Mid>
        std::enable_if_t<is_middleware_like_v<Mid>>
        use(const std::string& path, Mid ms);

    
        Middleware serve_static(const std::string& path);
    
        void print_routes () const;
    private:
        void _do_accept();
        void _handle_session(tcp::socket socket);
        void _log_routing (int64_t ms, const Request& req, Response& res) const;
    
        net::io_context ioc_;
        tcp::acceptor acceptor_;
        Router router_;
    };

    template <typename... Mids>
    std::enable_if_t<are_all_middlewares_v<Mids...>>
    HttpServer::use(const std::string& path, Mids... ms) {
        (use(path, ms), ...);
    }
    
    template <typename... Mids>
    std::enable_if_t<are_all_middlewares_v<Mids...>>
    HttpServer::use(Mids... ms) {
        (use(ms), ...);
    }
    

    template <typename Mid>
    std::enable_if_t<is_middleware_like_v<Mid>>
    HttpServer::use(const std::string& path, Mid middleware) {
        router_.use(path, middleware);
    }

    template <typename Mid>
    std::enable_if_t<is_middleware_like_v<Mid>>
    HttpServer::use(Mid middleware) {
        router_.use(middleware);
    }
}




#endif // HTTP_SERVER_HPP