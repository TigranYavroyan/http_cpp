// main.cpp
#include <thread>
#include <fstream>
#include <Router.h>
#include <post.h>
#include <get.h>
#include <handle_session.h>
#include <dotenv.h>
#include <middleware.h>
#include <next.h>
#include <middlewares.h>

void checking_parsed_object (Request& req, Response& res, Next& next) {
    auto body = req.parsed_body();
    if (body.value_or(0) != 0) {
        auto parsed = body.value();
        std::cout << "Parsed json: " << parsed << std::endl;
    }
    next();
}

int main() {
    dotenv::init("/home/tigran/Desktop/learn/http_cpp/.env");
    router.get("/", root);
    router.post("/submit", submit);
    router.get("/index.html", index_html);
    router.post("/user", pong);

    router.use(json_parser);
    router.use(checking_parsed_object);

    router.print_routes();
    std::string port = std::getenv("PORT");

    try {
        net::io_context ioc{1};
        tcp::acceptor acceptor{ioc, {tcp::v4(), static_cast<unsigned short>(std::stoi(port))}};

        std::cout << "Server running on http://localhost:" + port << std::endl;

        while (true) {
            tcp::socket socket{ioc};
            acceptor.accept(socket);
            std::thread{handle_session, std::move(socket)}.detach();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
