#include <http_server.h>
#include <thread>

HttpServer::HttpServer (int thread_count):
    ioc_{thread_count},
    acceptor_(ioc_)
{}

void HttpServer::listen (unsigned short port, Callback cb) {
    tcp::endpoint endpoint (tcp::v4(), port);
    try {
        acceptor_.open(endpoint.protocol());
        acceptor_.set_option(boost::asio::socket_base::reuse_address(true));
        acceptor_.bind(endpoint);
        acceptor_.listen();
        cb();
        _do_accept();
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
        throw;
    }
}

void HttpServer::get(const std::string& path, Handler handler) {
    router_.get(path, handler);
}

void HttpServer::post(const std::string& path, Handler handler) {
    router_.post(path, handler);
}

void HttpServer::del(const std::string& path, Handler handler) {
    router_.del(path, handler);
}

void HttpServer::update(const std::string& path, Handler handler) {
    router_.update(path, handler);
}

void HttpServer::put(const std::string& path, Handler handler) {
    router_.put(path, handler);
}

void HttpServer::patch(const std::string& path, Handler handler) {
    router_.patch(path, handler);
}

void HttpServer::use(const std::string& path, Middleware middleware) {
    router_.use(path, middleware);
}

void HttpServer::use(const std::string& path, MiddlewareFunc middleware) {
    router_.use(path, middleware);
}

void HttpServer::use(Middleware middleware) {
    router_.use(middleware);
}

void HttpServer::use(MiddlewareFunc middleware) {
    router_.use(middleware);
}

void HttpServer::print_routes () const {
    router_.print_routes();
}

void HttpServer::_do_accept() {
    try {
        while (true) {
            tcp::socket socket{ioc_};
            acceptor_.accept(socket);
            std::thread{&HttpServer::_handle_session, this, std::move(socket)}.detach();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void HttpServer::_handle_session(tcp::socket socket) {
    beast::flat_buffer buffer;
    BeastReq req;

    http::read(socket, buffer, req);

    BeastRes res{http::status::not_found, req.version()};
    res.set(http::field::server, "Boost.Beast");

    Request wrapper_req(std::move(req));
    Response wrapper_res(std::move(res));

    router_.route(wrapper_req, wrapper_res);

    http::write(socket, wrapper_res.raw());

    beast::error_code ec;
    socket.shutdown(tcp::socket::shutdown_send, ec);

    if(ec.failed()) {
        std::cerr << "Error: " << ec.message() << std::endl;
    }
}
