#include <Router.h>

void Router::get(const std::string& path, Handler handler) {
    routes_["GET:" + path] = std::move(handler);
}

void Router::post(const std::string& path, Handler handler) {
    routes_["POST:" + path] = std::move(handler);
}

bool Router::route(const Request& req, Response& res) const {
    std::string key = req.method_string().to_string() + ":" + req.target().to_string();
    auto it = routes_.find(key);
    if (it != routes_.end()) {
        it->second(req, res);
        return true;
    }
    return false;
}
