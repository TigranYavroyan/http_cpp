#ifndef ROUTER_H
#define ROUTER_H

#include <middleware.hpp>
#include <next.hpp>

class Router {
public:
    Router();

    void get(const std::string& path, Handler handler);
    void post(const std::string& path, Handler handler);

    void use(const std::string& path, Middleware middleware);
    void use(const std::string& path, MiddlewareFunc middleware);
    void use(Middleware middleware);
    void use(MiddlewareFunc middleware);

    bool route(Request& req, Response& res) const;
    void print_routes() const;
private:
    std::vector<Middleware> pre_handlers;
    std::unordered_map<std::string, Handler> routes_;
    std::unordered_multimap<std::string, Middleware> middlewares;
};

extern Router router;

#endif // ROUTER_H