#include <router.hpp>

Karich::Router::Router () {}

void Karich::Router::get(const std::string& path, Handler handler) {
    routes_["GET: " + path] = std::move(handler);
}

void Karich::Router::post(const std::string& path, Handler handler) {
    routes_["POST: " + path] = std::move(handler);
}

void Karich::Router::del(const std::string& path, Handler handler) {
    routes_["DELETE: " + path] = std::move(handler);
}

void Karich::Router::update(const std::string& path, Handler handler) {
    routes_["UPDATE: " + path] = std::move(handler);
}

void Karich::Router::put(const std::string& path, Handler handler) {
    routes_["PUT: " + path] = std::move(handler);
}

void Karich::Router::patch(const std::string& path, Handler handler) {
    routes_["PATCH: " + path] = std::move(handler);
}


bool Karich::Router::route(Karich::Request& req, Karich::Response& res) const {

    std::lock_guard<std::mutex> l(m);
    std::string path = req.url();
    std::string key = req.method() + ": " + path;
    auto it = routes_.find(key);
    
    std::vector<Karich::Middleware> router_spec_middlewares = pre_handlers;

    if (it != routes_.end()) {
        auto [begin, end] = middlewares.equal_range(path);
        for(; begin != end; ++begin) {
            router_spec_middlewares.push_back(begin->second);
        }
        router_spec_middlewares.emplace_back([handler = it->second](Karich::Request& req, Karich::Response& res, Karich::Next& next){
            handler(req, res);
        });
    }

    Karich::Next next(router_spec_middlewares, req, res);

    return next();
}

void Karich::Router::print_routes() const {
    std::cout << " ----- Listening on this routes ----- " << std::endl;
    for (auto& it : routes_) {
        std::cout << it.first << std::endl;
    }
    std::cout <<  "-------------------------------------" << std::endl;
}