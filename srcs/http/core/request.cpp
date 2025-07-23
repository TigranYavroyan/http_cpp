#include <request.h>

Request::Request (BeastReq& req) : req_(std::move(req)) {}

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
    return req_.target().to_string();
}

std::string Request::method () const {
    return req_.method_string().to_string();
}