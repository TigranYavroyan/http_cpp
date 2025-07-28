#include <router.h>
#include <post.h>
#include <get.h>
#include <utils.h>
#include <dotenv.h>
#include <middleware.h>
#include <next.h>
#include <middlewares.h>
#include <http_server.h>

int main() {
    dotenv::init("../.env");
    std::string port = std::getenv("PORT");
    project_root = std::getenv("PROJECT_ROOT");

    Karich::HttpServer http_server;

    http_server.post("/submit", submit);
    http_server.post("/user", pong);

    http_server.use(json_parser);
    http_server.use(http_server.serve_static("../public"));

    http_server.listen(std::stoi(port), [&](){
        std::cout << "Listening on port " << port << "...\n" << std::endl;
        http_server.print_routes();
    });
}
