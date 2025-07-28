#include <http_server.h>
#include <thread>
#include <utils.h>
#include <is_middleware.hpp>

Karich::HttpServer::HttpServer (int thread_count):
    ioc_{thread_count},
    acceptor_(ioc_)
{}

void Karich::HttpServer::listen (unsigned short port, Callback cb) {
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

void Karich::HttpServer::get(const std::string& path, Handler handler) {
    router_.get(path, handler);
}

void Karich::HttpServer::post(const std::string& path, Handler handler) {
    router_.post(path, handler);
}

void Karich::HttpServer::del(const std::string& path, Handler handler) {
    router_.del(path, handler);
}

void Karich::HttpServer::update(const std::string& path, Handler handler) {
    router_.update(path, handler);
}

void Karich::HttpServer::put(const std::string& path, Handler handler) {
    router_.put(path, handler);
}

void Karich::HttpServer::patch(const std::string& path, Handler handler) {
    router_.patch(path, handler);
}

void Karich::HttpServer::use(const std::string& path, Middleware middleware) {
    router_.use(path, middleware);
}

void Karich::HttpServer::use(const std::string& path, MiddlewareFunc middleware) {
    router_.use(path, middleware);
}

void Karich::HttpServer::use(const std::string& path, MiddlewareFuncPtr middleware) {
    router_.use(path, middleware);
}

void Karich::HttpServer::use(Middleware middleware) {
    router_.use(middleware);
}

void Karich::HttpServer::use(MiddlewareFunc middleware) {
    router_.use(middleware);
}

void Karich::HttpServer::use(MiddlewareFuncPtr middleware) {
    router_.use(middleware);
}

void Karich::HttpServer::print_routes () const {
    router_.print_routes();
}

void Karich::HttpServer::_do_accept() {
    try {
        while (true) {
            tcp::socket socket{ioc_};
            acceptor_.accept(socket);
            std::thread{&Karich::HttpServer::_handle_session, this, std::move(socket)}.detach();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void Karich::HttpServer::_handle_session(tcp::socket socket) {
    try {
        beast::flat_buffer buffer;
        BeastReq req;

        http::read(socket, buffer, req);

        BeastRes res{http::status::not_found, req.version()};
        res.set(http::field::server, "Boost.Beast");

        Karich::Request wrapper_req(std::move(req));
        Karich::Response wrapper_res(std::move(res));

        auto [ms, routed] = Karich::utils::time_calculate<bool>([&]() {
            return router_.route(wrapper_req, wrapper_res);
        });

        if (!routed)
            std::cerr << "Middlewares doesn't pass\n";

        _log_routing(ms, wrapper_req, wrapper_res);

        http::write(socket, wrapper_res.raw());

        beast::error_code ec;
        socket.shutdown(tcp::socket::shutdown_send, ec);
        if(ec) {
            std::cerr << "Error: " << ec.message() << std::endl;
        }
    } 
    catch (const boost::system::system_error& se) {
        if (se.code() == http::error::end_of_stream) {
            std::cerr << "Client closed connection early.\n" << std::endl;
            return;
        } else {
            std::cerr << "System error: " << se.code().message() << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Session Error: " << e.what() << std::endl;
    }
}

void Karich::HttpServer::_log_routing (int64_t ms, const Karich::Request& req, Karich::Response& res) const {
    std::cout << "[" << req.method() << "] "
                  << req.url() << " -> "
                  << static_cast<unsigned>(res.raw().result_int()) << " "
                  << res.raw().result() << " ("
                  << ms << " ms)" << std::endl;
}

Middleware Karich::HttpServer::serve_static (const std::string& path) {
    return Middleware([&path](Karich::Request& req, Karich::Response& res, Next& next){
        std::string target = req.url();
        if (target == "/")
            target = "/index.html";

        fs::path file_path = fs::path(path + target);

        if (fs::exists(file_path) && fs::is_regular_file(file_path)) {
            std::ifstream file(file_path, std::ios::binary);
            if (!file.is_open()) {
                res.send("Failed to open file").status(http::status::internal_server_error);
                return;
            }

            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            res.set_header(http::field::content_type, Karich::utils::get_mime_type(file_path.string()));
            res.send(std::move(content)).status(http::status::ok);
            file.close();
            return;
        }

        // Not a static file — pass to next middleware or handler
        next();
    });
}