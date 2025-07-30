#include <request.h>

namespace Karich {
    Request::Request (BeastReq&& req) : req_(std::move(req)) {
        std::string full_url = std::string(req_.target());
        std::size_t query_begin = full_url.find('?');
        
        if (query_begin == boost::beast::string_view::npos) {
            url_ = full_url;
            return;
        }

        _parse_query(full_url, query_begin);

        if (url_.find(':') == std::string::npos)
            return;
    }
    
    BeastReq& Request::raw () {
        return req_;
    }
    
    void Request::set_body (const json& body) {
        json_body_ = body;
    }
    
    std::optional<json> Request::parsed_body () const {
        return json_body_;
    }
    
    std::string Request::body () const {
        return req_.body();
    }
    
    std::string Request::url () const {
        return url_;
    }
    
    std::string Request::method () const {
        return std::string(req_.method_string());
    }

    std::unordered_multimap<std::string, std::string> Request::queries () const {
        return queries_;
    }

    void Request::_parse_query (const std::string& full_url, std::size_t query_begin) {
        url_ = full_url.substr(0, query_begin);

        std::string query(full_url, query_begin + 1, full_url.size() - query_begin);
        std::size_t start = 0;
        std::string key;
        std::string val;

        while (start < query.size()) {
            auto end = query.find('&', start);
            if (end == std::string::npos) end = query.size();

            auto sep = query.find('=', start);
            if (sep != std::string::npos && sep < end) {
                key = query.substr(start, sep - start);
                val = query.substr(sep + 1, end - sep - 1);
                queries_.insert({key, val});
            }
            else if (sep == std::string::npos || end == query.size() || query[end] == '&') {
                key = query.substr(start, end - start);
                if (!key.empty())
                    queries_.insert({key, ""});
            }

            start = end + 1;
        }
    }
}