// main.cpp
#include <Router.h>
#include <post.h>
#include <get.h>
#include <handle_session.h>
#include <dotenv.h>
#include <middleware.h>
#include <next.h>
#include <middlewares.h>
#include <http_server.h>

void checking_parsed_object (Request& req, Response& res, Next& next) {
    auto body = req.parsed_body();
    if (body.value_or(0) != 0) {
        auto parsed = body.value();
        std::cout << "Parsed json: " << parsed << std::endl;
        next();
    }
    else {
        res.err();
    }
}

int main() {
    dotenv::init("/home/tigran/Desktop/learn/http_cpp/.env");
    HttpServer http_server;

    router.get("/", root);
    router.post("/submit", submit);
    router.get("/index.html", index_html);
    router.post("/user", pong);

    router.use(json_parser);
    router.use(checking_parsed_object);

    router.print_routes();
    std::string port = std::getenv("PORT");

    http_server.listen(std::stoi(port), [&port](){
        std::cout << "Listening on port " << port << "..." << std::endl;
    });
}
