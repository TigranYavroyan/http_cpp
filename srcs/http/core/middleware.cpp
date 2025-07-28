#include <middleware.h>


Karich::Middleware::Middleware(Karich::MiddlewareFunc func) : func_(std::move(func)) {}

void Karich::Middleware::operator() (Karich::Request& req, Karich::Response& res, Karich::Next& next) {
    func_(req, res, next);
}

Karich::Middleware::~Middleware() = default;