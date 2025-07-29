#include <router.hpp>

namespace Karich {
    Router::Router () {}
    
    void Router::get(const std::string& path, Handler handler) {
        routes_["GET"][path] = std::move(handler);
    }
    
    void Router::post(const std::string& path, Handler handler) {
        routes_["POST"][path] = std::move(handler);
    }
    
    void Router::del(const std::string& path, Handler handler) {
        routes_["DELETE"][path] = std::move(handler);
    }
    
    void Router::update(const std::string& path, Handler handler) {
        routes_["UPDATE"][path] = std::move(handler);
    }
    
    void Router::put(const std::string& path, Handler handler) {
        routes_["PUT"][path] = std::move(handler);
    }
    
    void Router::patch(const std::string& path, Handler handler) {
        routes_["PATCH"][path] = std::move(handler);
    }
    
    bool Router::route(Request& req, Response& res) const {
    
        std::lock_guard<std::mutex> l(m);
        std::string path = req.url();
    
        auto pair = routes_.find(req.method());
        UnderlyingRouteHandler map;
        Router::UnderlyingRouteHandler::iterator it(map.end());
    
        if (pair != routes_.end()) {
            map = pair->second;
            it = map.find(path);
        }
        
        std::vector<Middleware> router_spec_middlewares = pre_handlers;
    
        if (it != map.end()) {
            auto [begin, end] = middlewares.equal_range(path);
            for(; begin != end; ++begin) {
                router_spec_middlewares.push_back(begin->second);
            }
            router_spec_middlewares.emplace_back([handler = it->second](Request& req, Response& res, Next& next){
                handler(req, res);
            });
        }
    
        Next next(router_spec_middlewares, req, res);
    
        return next();
    }
    
    void Router::print_routes() const {
        std::cout << " ----- Listening on this routes ----- " << std::endl;
        for (auto& it : routes_) {
            for (auto& [route, _] : it.second) {
                std::cout << it.first << ": " << route << std::endl;
            }
        }
        std::cout <<  "-------------------------------------" << std::endl;
    }

    void Router::_use_handler (const std::string& method, const std::string& path, Handler h) {
        routes_[method][path] = std::move(h);
    }
}