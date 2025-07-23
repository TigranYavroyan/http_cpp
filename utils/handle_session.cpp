#include <handle_session.h>
#include <Router.h>

void handle_session(tcp::socket socket) {
    beast::flat_buffer buffer;
    BeastReq req;

    http::read(socket, buffer, req);

    BeastRes res{http::status::not_found, req.version()};
    res.set(http::field::server, "Boost.Beast");

    Request wrapper_req(req);
    Response wrapper_res(res);

    if (!router.route(wrapper_req, wrapper_res)) {
        wrapper_res.err();
    }

    http::write(socket, wrapper_res.raw());

    beast::error_code ec;
    socket.shutdown(tcp::socket::shutdown_send, ec);

    if(ec.failed()) {
        std::cerr << "Error: " << ec.message() << std::endl;
    }
}
