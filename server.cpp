// main.cpp
#include <thread>
#include <fstream>
#include <Router.h>

void handle_session(tcp::socket socket) {
    beast::flat_buffer buffer;
    Request req;

    http::read(socket, buffer, req);

    Response res{http::status::not_found, req.version()};
    res.set(http::field::server, "Boost.Beast");

    if (!router.route(req, res)) {
        res.set(http::field::content_type, "text/plain");
        res.body() = "404 Not Found";
        res.prepare_payload();
    }

    http::write(socket, res);

    beast::error_code ec;
    socket.shutdown(tcp::socket::shutdown_send, ec);
}


int main() {

    // This can added in another src file with controllers and services
    router.get("/", [](const Request& req, Response& res) {
        res.result(http::status::ok);
        res.set(http::field::content_type, "text/html");
        res.body() = "<h1>Hello from router</h1>";
        res.prepare_payload();
    });

    router.post("/submit", [](const Request& req, Response& res) {
        res.result(http::status::ok);
        res.set(http::field::content_type, "text/plain");
        res.body() = "You posted: " + req.body();
        res.prepare_payload();
    });

    router.get("/index.html", [](const Request& req, Response& res) {
        std::ifstream file("/home/tigran/Desktop/learn/http_cpp/public/index.html");
        if (!file) {
            http::response<http::string_body> res{http::status::not_found, req.version()};
            res.set(http::field::content_type, "text/plain");
            res.body() = "File not found.";
            res.prepare_payload();
            return;
        }

        std::string content((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
        
        res.body() = content;
        res.result(http::status::ok);
        res.set(http::field::content_type, "text/html");
        res.prepare_payload();
    });

    try {
        net::io_context ioc{1};
        tcp::acceptor acceptor{ioc, {tcp::v4(), 8080}};

        std::cout << "Server running on http://localhost:8080\n";

        while (true) {
            tcp::socket socket{ioc};
            acceptor.accept(socket);
            std::thread{handle_session, std::move(socket)}.detach();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
