#include <post.h>

void submit (Karich::Request& req, Karich::Response& res) {
    res.set_header(http::field::content_type, "text/plain");
    res.send("You posted " + req.body()).status(200);
}

void pong (Karich::Request& req, Karich::Response& res) {
    res.status(http::status::ok);
    json r = {
        {"type", "send by server"},
        {"name", "Artur"},
        {"age", 18}
    };

    res.json(r);
}