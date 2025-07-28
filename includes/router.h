#ifndef ROUTER_H
#define ROUTER_H

#include <middleware.h>
#include <next.h>
#include <mutex>

class Router {
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

    void use(const std::string& path, Middleware middleware);
    void use(const std::string& path, MiddlewareFunc middleware);
    void use(const std::string& path, MiddlewareFuncPtr middleware);
    void use(Middleware middleware);
    void use(MiddlewareFunc middleware);
    void use(MiddlewareFuncPtr middleware);

    bool route(Karich::Request& req, Karich::Response& res) const;
    void print_routes() const;
private:
    std::vector<Middleware> pre_handlers;
    std::unordered_map<std::string, Handler> routes_;
    std::unordered_multimap<std::string, Middleware> middlewares;
    mutable std::mutex m;
};

#endif // ROUTER_H