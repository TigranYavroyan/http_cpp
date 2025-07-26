#include <router.h>
#include <post.h>
#include <get.h>
#include <handle_session.h>
#include <dotenv.h>
#include <middleware.h>
#include <next.h>
#include <middlewares.h>
#include <http_server.h>

void log3 (Request& req, Response& res, Next& next) {
    std::cout << __func__ << std::endl;
    std::cout << req.body() << std::endl;
    next();
};

int main() {
    dotenv::init("/home/tigran/Desktop/learn/http_cpp/.env");
    std::string port = std::getenv("PORT");

    HttpServer http_server;

    MiddlewareFunc log4 = [](Request& req, Response& res, Next& next){
        std::cout << __func__ << std::endl;
        std::cout << req.body() << std::endl;
        next();
    };

    Middleware m(log3);

    http_server.get("/", root);
    http_server.post("/submit", submit);
    http_server.get("/index.html", index_html);
    http_server.post("/user", pong);

    http_server.use(json_parser, m, log3, log4);
    http_server.use("/submit", json_parser, m, log3, log4);

    http_server.listen(std::stoi(port), [&](){
        std::cout << "Listening on port " << port << "...\n" << std::endl;
        http_server.print_routes();
    });
}
