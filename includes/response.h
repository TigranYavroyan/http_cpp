#ifndef RESPONSE_H
#define RESPONSE_H

#include <includes.h>

class Response {
public:
    Response();
    Response(BeastRes& res);
public:
    Response& set_header(const std::string& key, const std::string& value);
    Response& set_header(boost::beast::http::field field, const std::string& value);

    Response& status(int code);
    Response& status(boost::beast::http::status s);

    Response& send(const std::string& body);
    Response& json(const nlohmann::json& obj);
    Response& err(const std::string& msg = "Not found");
    BeastRes& raw();
    bool is_sent() const;
private:
    BeastRes res_;
    bool sent_;
};

#endif // RESPONSE_H