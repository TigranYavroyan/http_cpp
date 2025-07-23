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

void mid (Request& req, Response& res, Next& next) {
    std::cout << "The req body:" <<  req.body() << std::endl;
    if (/** fstan */true) {
        next();
    }
}

void logger (Request& req, Response& res, Next& next) {
    std::cout << "Logging request: " << req.target() << "\n";
    next(); // Calls next middleware in chain
}

void validator (Request& req, Response& res, Next& next) {
    json body = json::parse(req.body());
    if (body.contains("valid")) {
        std::cout << "Got valid obj" << std::endl;
        next();
    }
}

int main() {
    dotenv::init("/home/tigran/Desktop/learn/http_cpp/.env");
    router.get("/", root);
    router.post("/submit", submit);
    router.get("/index.html", index_html);
    router.post("/user", pong);

    router.use(validator);
    router.use("/submit", Middleware(mid));
    router.use("/submit", Middleware(logger));

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
