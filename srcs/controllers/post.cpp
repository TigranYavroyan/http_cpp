#include <post.h>

void submit (const Request& req, Response& res) {
    res.result(http::status::ok);
    res.set(http::field::content_type, "text/plain");
    res.body() = "You posted: " + req.body();
    res.prepare_payload();
}

void pong (const Request& req, Response& res) {
    std::cout << req.body() << std::endl;
    res.result(http::status::ok);
    json r = {
        {"name", "Artur"},
        {"age", 18}
    };

    res.body() = r.dump();
    res.prepare_payload();
}