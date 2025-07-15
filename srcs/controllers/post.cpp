#include <post.h>

void submit (const Request& req, Response& res) {
    res.result(http::status::ok);
    res.set(http::field::content_type, "text/plain");
    res.body() = "You posted: " + req.body();
    res.prepare_payload();
}