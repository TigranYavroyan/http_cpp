#include <post.h>

void submit (Request& req, Response& res) {
    res.set_header(http::field::content_type, "text/plain");
    res.send("You posted " + req.body());
}

void pong (Request& req, Response& res) {
    std::cout << req.body() << std::endl;
    res.status(http::status::ok);
    json r = {
        {"type", "send by server"},
        {"name", "Artur"},
        {"age", 18}
    };

    res.json(r);
}