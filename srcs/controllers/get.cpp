#include <get.h>

void root (Request& req, Response& res) {
    res.set_header(http::field::content_type, "text/html");
    res.send("<h1>Hello from router</h1>");
}

void index_html (Request& req, Response& res) {
    std::ifstream file("/home/tigran/Desktop/learn/http_cpp/public/index.html");
    if (!file) {
        res.send("File not found");
        return;
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    res.set_header(boost::beast::http::field::content_type, "text/html");
    res.send(content);
}