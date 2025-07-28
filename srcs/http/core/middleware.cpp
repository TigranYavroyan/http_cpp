#include <middleware.h>


Middleware::Middleware(MiddlewareFunc func) : func_(std::move(func)) {}

void Middleware::operator() (Karich::Request& req, Karich::Response& res, Next& next) {
    func_(req, res, next);
}

Middleware::~Middleware() = default;