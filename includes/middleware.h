#ifndef MIDDLEWARE_HPP
#define MIDDLEWARE_HPP

#include <includes.h>
#include <request.h>
#include <response.h>

class Next;
class Middleware;

using MiddlewareFunc = std::function<void(Request&, Response&, Next&)>;
using MiddlewareFuncPtr = void(*)(Request&, Response&, Next&);

class Middleware {
public:
    Middleware(MiddlewareFunc func);
    void operator() (Request& req, Response& res, Next& next);
    virtual ~Middleware();
private:
    MiddlewareFunc func_;
};

#endif // MIDDLEWARE_HPP