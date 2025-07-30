#ifndef REQUEST_H
#define REQUEST_H

#include <includes.h>

namespace Karich {

    class Request {
    public:
        // !later remove the copying
        Request () = default;
        Request (BeastReq&& req);
    public:
        BeastReq& raw ();
        void set_body (const json& body);
        std::optional<json> parsed_body () const;
        std::string body () const;
        std::unordered_multimap<std::string, std::string> queries () const;
        std::string url () const;
        std::string method () const;
    private:
        void _parse_query (const std::string& full_url, std::size_t query_begin);

        BeastReq req_;
        std::optional<json> json_body_;
        std::unordered_multimap<std::string, std::string> queries_;
        std::string url_;
    };

}

#endif // REQUEST_H