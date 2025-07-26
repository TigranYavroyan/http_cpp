// main.cpp
#include <router.h>
#include <post.h>
#include <get.h>
#include <handle_session.h>
#include <dotenv.h>
#include <middleware.h>
#include <next.h>
#include <middlewares.h>
#include <http_server.h>

int main() {
    dotenv::init("/home/tigran/Desktop/learn/http_cpp/.env");
    std::string port = std::getenv("PORT");

    HttpServer http_server;

    http_server.get("/", root);
    http_server.post("/submit", submit);
    http_server.get("/index.html", index_html);
    http_server.post("/user", pong);

    http_server.use(json_parser);

    http_server.listen(std::stoi(port), [&](){
        std::cout << "Listening on port " << port << "..." << std::endl;
        http_server.print_routes();
    });
}
