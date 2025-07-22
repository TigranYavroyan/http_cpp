#include <post.h>

void submit (Request& req, Response& res) {
    res.result(http::status::ok);
    res.set(http::field::content_type, "text/plain");
    res.body() = "You posted: " + req.body();
    res.prepare_payload();
}

void pong (Request& req, Response& res) {
    std::cout << req.body() << std::endl;
    res.result(http::status::ok);
    json r = {
        {"type", "send by server"},
        {"name", "Artur"},
        {"age", 18}
    };

    res.body() = r.dump();
    res.prepare_payload();
}