#include <middleware.h>

namespace Karich {
    Middleware::Middleware(MiddlewareFunc func) : func_(std::move(func)) {}
    
    void Middleware::operator() (Request& req, Response& res, Next& next) {
        func_(req, res, next);
    }
    
    Middleware::~Middleware() = default;
}