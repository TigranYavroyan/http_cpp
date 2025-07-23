#ifndef REQUEST_H
#define REQUEST_H

#include <includes.h>

class Request {
public:
    Request () = default;
    Request (BeastReq& req);
    ~Request () = default;
public:
    BeastReq& raw ();
    void set_body (const json& body);
    std::optional<json> parsed_body () const;
    std::string body () const;
    std::string url () const;
    std::string method () const;
private:
    BeastReq req_;
    std::optional<json> json_body;
};

#endif // REQUEST_H