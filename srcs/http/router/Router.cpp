#include <Router.h>

Router::Router () {}

void Router::get(const std::string& path, Handler handler) {
    routes_["GET: " + path] = std::move(handler);
}

void Router::post(const std::string& path, Handler handler) {
    routes_["POST: " + path] = std::move(handler);
}

void Router::del(const std::string& path, Handler handler) {
    routes_["DELETE: " + path] = std::move(handler);
}

void Router::update(const std::string& path, Handler handler) {
    routes_["UPDATE: " + path] = std::move(handler);
}

void Router::put(const std::string& path, Handler handler) {
    routes_["PUT: " + path] = std::move(handler);
}

void Router::patch(const std::string& path, Handler handler) {
    routes_["PATCH: " + path] = std::move(handler);
}


bool Router::route(Request& req, Response& res) const {
    std::lock_guard<std::mutex> l(m);
    std::string path = req.url();
    std::string key = req.method() + ": " + path;
    auto it = routes_.find(key);
    if (it == routes_.end())
        return false;

    std::vector<Middleware> router_spec_middlewares = pre_handlers;
    auto [begin, end] = middlewares.equal_range(path);
    for(; begin != end; ++begin) {
        router_spec_middlewares.push_back(begin->second);
    }

    router_spec_middlewares.emplace_back([handler = it->second](Request& req, Response& res, Next& next){
        handler(req, res);
    });

    Next next(router_spec_middlewares, req, res);

    return next();
}

void Router::use(const std::string& path, Middleware middleware) {
    middlewares.insert({path, middleware});
}

void Router::use(const std::string& path, MiddlewareFunc middleware) {
    middlewares.insert({path, middleware});
}

void Router::use(Middleware middleware) {
    pre_handlers.push_back(middleware);
}

void Router::use(MiddlewareFunc middleware) {
    pre_handlers.emplace_back(middleware);
}

void Router::print_routes() const {
    std::cout << " ----- Listening on this routes ----- " << std::endl;
    for (auto& it : routes_) {
        std::cout << it.first << std::endl;
    }
    std::cout <<  "-------------------------------------" << std::endl;
}