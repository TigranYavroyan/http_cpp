#ifndef ROUTER_H
#define ROUTER_H

#include <middleware.h>
#include <is_middleware.hpp>
#include <next.h>
#include <mutex>


namespace Karich {
    class HttpServer;

    class Router {
        friend HttpServer;
        using UnderlyingRouteHandler = std::unordered_map<std::string, Handler>;
        using RouteHandlers = std::unordered_map<std::string, UnderlyingRouteHandler>;
        using MiddlewareHandlers = std::unordered_multimap<std::string, Middleware>;
    public:
        Router();
    
        Router (const Router&) = delete;
        Router& operator= (const Router&) = delete;
        Router (Router&& other) = delete;
        Router& operator= (Router&& other) = delete;
    
        void get(const std::string& path, Handler handler);
        void post(const std::string& path, Handler handler);
        void del(const std::string& path, Handler handler);
        void update(const std::string& path, Handler handler);
        void put(const std::string& path, Handler handler);
        void patch(const std::string& path, Handler handler);
    
        template <typename Mid>
        std::enable_if_t<is_middleware_like_v<Mid>>
        use(Mid ms);
    
        template <typename Mid>
        std::enable_if_t<is_middleware_like_v<Mid>>
        use(const std::string& path, Mid ms);
    
        bool route(Request& req, Response& res) const;
        void print_routes() const;
    private:
        void _use_handler (const std::string& method, const std::string& path, Handler h);

        std::vector<Middleware> pre_handlers;
        RouteHandlers routes_;
        MiddlewareHandlers middlewares;
        mutable std::mutex m;
    };

    template <typename Mid>
    std::enable_if_t<is_middleware_like_v<Mid>>
    Router::use(const std::string& path, Mid middleware) {
        middlewares.insert({path, Middleware(middleware)});
    }

    template <typename Mid>
    std::enable_if_t<is_middleware_like_v<Mid>>
    Router::use(Mid middleware) {
        pre_handlers.push_back(Middleware(middleware));
    }
}

#endif // ROUTER_H