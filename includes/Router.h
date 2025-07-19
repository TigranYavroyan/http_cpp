#ifndef ROUTER_H
#define ROUTER_H

#include <includes.h>

class Router {
public:
    Router();

    void get(const std::string& path, Handler handler);
    void post(const std::string& path, Handler handler);
    bool route(const Request& req, Response& res) const;
    void print_routes() const;
private:
    std::unordered_map<std::string, Handler> routes_;
};

extern Router router;

#endif // ROUTER_H