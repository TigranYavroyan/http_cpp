#include <request.h>

namespace Karich {
    Request::Request (BeastReq&& req) : req_(std::move(req)) {}
    
    BeastReq& Request::raw () {
        return req_;
    }
    
    void Request::set_body (const json& body) {
        json_body = body;
    }
    
    std::optional<json> Request::parsed_body () const {
        return json_body;
    }
    
    std::string Request::body () const {
        return req_.body();
    }
    
    std::string Request::url () const {
        return std::string(req_.target());
    }
    
    std::string Request::method () const {
        return std::string(req_.method_string());
    }
}