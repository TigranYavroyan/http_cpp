// main.cpp
#include <thread>
#include <fstream>
#include <Router.h>
#include <post.h>
#include <get.h>
#include <handle_session.h>

int main() {

    router.get("/", root);
    router.post("/submit", submit);
    router.get("/index.html", index_html);

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
