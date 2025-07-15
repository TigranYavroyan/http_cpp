#include <handle_session.h>
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

    if(ec.failed()) {
        std::cerr << "Error: " << ec.message() << std::endl;
    }
}
