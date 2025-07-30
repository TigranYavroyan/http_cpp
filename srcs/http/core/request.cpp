#include <request.h>

namespace Karich {
    Request::Request (BeastReq&& req) : req_(std::move(req)) {
        auto full_url = req_.target();
        auto query_begin = full_url.find('?');
        
        if (query_begin == boost::beast::string_view::npos) {
            url_ = std::string(full_url);
            return;
        }
        
        url_ = full_url.substr(0, query_begin);
        std::string query(full_url, query_begin + 1, full_url.size() - query_begin);
        std::cout << query << std::endl;
        std::size_t start = 0;

        // ! not handling edge cases
        while (start < query.size()) {
            auto end = query.find('&', start);
            if (end == std::string::npos) end = query.size();

            auto sep = query.find('=', start);
            if (sep != std::string::npos && sep < end) {
                std::string key = query.substr(start, sep - start);
                std::string val = query.substr(sep + 1, end - sep - 1);
                queries_[key] = val;
            }

            start = end + 1;
        }
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

    std::unordered_map<std::string, std::string> Request::queries () const {
        return queries_;
    }
}