#ifndef MIDDLEWARE_HPP
#define MIDDLEWARE_HPP

#include <includes.h>
#include <request.h>
#include <response.h>

class Next;
class Middleware;

using MiddlewareFunc = std::function<void(Karich::Request&, Karich::Response&, Next&)>;
using MiddlewareFuncPtr = void(*)(Karich::Request&, Karich::Response&, Next&);

class Middleware {
public:
    Middleware(MiddlewareFunc func);
    void operator() (Karich::Request& req, Karich::Response& res, Next& next);
    virtual ~Middleware();
private:
    MiddlewareFunc func_;
};

#endif // MIDDLEWARE_HPP