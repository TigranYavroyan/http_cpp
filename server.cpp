#include <cstring>
#include <router.hpp>
#include <post.h>
#include <get.h>
#include <utils.h>
#include <dotenv.h>
#include <middleware.h>
#include <next.h>
#include <middlewares.h>
#include <http_server.hpp>
#include <globals.h>
#include <request.h>

using namespace Karich;

int main() {
    std::string env_path = globals::get_project_root() + ".env";
    dotenv::init(env_path.c_str());
    std::string port = std::getenv("PORT");

    HttpServer http_server;
    Router r = Router();

    r.get("/name", [](Request& req, Response& res){
        res.send("My name is gegham").status(200);
        auto params = req.params();
        for (auto [key, value] : params) {
            std::cout << key << ": " << value << std::endl;
        }
    });

    r.post("/name", [](Request& req, Response& res){
        std::string name = req.parsed_body().value()["name"];
        res.send("Your name is " + name).status(200);
    });

    http_server.post("/submit", submit);
    http_server.use("/user", r);

    http_server.use(json_parser);
    http_server.use(http_server.serve_static(globals::get_project_root() + "public"));

    http_server.listen(std::stoi(port), [&](){
        std::cout << "Listening on port " << port << "...\n" << std::endl;
        http_server.print_routes();
    });
}
