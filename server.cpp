#include <router.h>
#include <post.h>
#include <get.h>
#include <utils.h>
#include <dotenv.h>
#include <middleware.h>
#include <next.h>
#include <middlewares.h>
#include <http_server.h>
#include <cstring>

int main() {
    #ifdef PROJECT_ROOT
        Karich::globals::project_root = PROJECT_ROOT;
        {
            std::string env_path = Karich::globals::project_root + ".env";
            dotenv::init(env_path.c_str());
        }
    #else
        std::cout << "Define the project root folder" << std::endl;
        return (EXIT_FAILURE);
    #endif
    std::string port = std::getenv("PORT");

    Karich::HttpServer http_server;

    http_server.post("/submit", submit);
    http_server.post("/user", pong);

    http_server.use(json_parser);
    http_server.use(http_server.serve_static(Karich::globals::project_root + "public"));


    http_server.listen(std::stoi(port), [&](){
        std::cout << "Listening on port " << port << "...\n" << std::endl;
        http_server.print_routes();
    });
}
