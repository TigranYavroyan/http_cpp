#include <get.h>

void root (const Request& req, Response& res) {
    res.result(http::status::ok);
    res.set(http::field::content_type, "text/html");
    res.body() = "<h1>Hello from router</h1>";
    res.prepare_payload();
}

void index_html (const Request& req, Response& res) {
    std::ifstream file("/home/tigran/Desktop/learn/http_cpp/public/index.html");
    if (!file) {
        http::response<http::string_body> res{http::status::not_found, req.version()};
        res.set(http::field::content_type, "text/plain");
        res.body() = "File not found.";
        res.prepare_payload();
        return;
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    
    res.body() = content;
    res.result(http::status::ok);
    res.set(http::field::content_type, "text/html");
    res.prepare_payload();  
}