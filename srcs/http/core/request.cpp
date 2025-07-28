#include <request.h>

Karich::Request::Request (BeastReq&& req) : req_(std::move(req)) {}

BeastReq& Karich::Request::raw () {
    return req_;
}

void Karich::Request::set_body (const json& body) {
    json_body = body;
}

std::optional<json> Karich::Request::parsed_body () const {
    return json_body;
}

std::string Karich::Request::body () const {
    return req_.body();
}

std::string Karich::Request::url () const {
    return req_.target().to_string();
}

std::string Karich::Request::method () const {
    return req_.method_string().to_string();
}