#include <response.h>

namespace Karich {
    Response::Response() : sent_(false) {
            res_.version(11);
            res_.keep_alive(true);
    }
    
    Response::Response(BeastRes&& res) : res_(std::move(res)), sent_(false) {}
    
    Response& Response::set_header(const std::string& key, const std::string& value) {
        res_.set(key, value);
        return *this;
    }
    
    Response& Response::set_header(beast::http::field field, const std::string& value) {
        res_.set(field, value);
        return *this;
    }
    
    Response& Response::set_header(beast::http::field field, const std::string_view& value) {
        res_.set(field, std::move(std::string(value)));
        return *this;
    }
    
    Response& Response::set_header(beast::http::field field, const char* value) {
        res_.set(field, value);
        return *this;
    }
    
    
    Response& Response::status(int code) {
        res_.result(static_cast<beast::http::status>(code));
        return *this;
    }
    
    Response& Response::status(beast::http::status s) {
        res_.result(s);
        return *this;
    }
    
    Response& Response::err(const std::string& msg) {
        res_.set(http::field::content_type, "text/plain");
        res_.result(beast::http::status::not_found);
        send(msg);
        return *this;
    }
    
    Response& Response::send(const std::string& body) {
        if (sent_)
            return *this;
    
        res_.body() = body;
        res_.prepare_payload();
        sent_ = true;
        return *this;
    }
    
    Response& Response::json(const nlohmann::json& obj) {
        set_header("Content-Type", "application/json");
        send(obj.dump());
        return *this;
    }
    
    BeastRes& Response::raw() {
        return res_;
    }
    
    bool Response::is_sent() const {
        return sent_;
    }
    
    void Response::reset() {
        res_ = {};
        sent_ = false;
        res_.version(11);
        res_.keep_alive(true);
    }
}