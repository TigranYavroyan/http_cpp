#include <response.h>

Karich::Response::Response() : sent_(false) {
        res_.version(11);
        res_.keep_alive(true);
}

Karich::Response::Response(BeastRes&& res) : res_(std::move(res)), sent_(false) {}

Karich::Response& Karich::Response::set_header(const std::string& key, const std::string& value) {
    res_.set(key, value);
    return *this;
}

Karich::Response& Karich::Response::set_header(beast::http::field field, const std::string& value) {
    res_.set(field, value);
    return *this;
}

Karich::Response& Karich::Response::set_header(beast::http::field field, const std::string_view& value) {
    res_.set(field, std::move(std::string(value)));
    return *this;
}

Karich::Response& Karich::Response::set_header(beast::http::field field, const char* value) {
    res_.set(field, value);
    return *this;
}


Karich::Response& Karich::Response::status(int code) {
    res_.result(static_cast<beast::http::status>(code));
    return *this;
}

Karich::Response& Karich::Response::status(beast::http::status s) {
    res_.result(s);
    return *this;
}

Karich::Response& Karich::Response::err(const std::string& msg) {
    res_.set(http::field::content_type, "text/plain");
    res_.result(beast::http::status::not_found);
    send(msg);
    return *this;
}

Karich::Response& Karich::Response::send(const std::string& body) {
    if (sent_)
        return *this;

    res_.body() = body;
    res_.prepare_payload();
    sent_ = true;
    return *this;
}

Karich::Response& Karich::Response::json(const nlohmann::json& obj) {
    set_header("Content-Type", "application/json");
    send(obj.dump());
    return *this;
}

BeastRes& Karich::Response::raw() {
    return res_;
}

bool Karich::Response::is_sent() const {
    return sent_;
}

void Karich::Response::reset() {
    res_ = {};
    sent_ = false;
    res_.version(11);
    res_.keep_alive(true);
}