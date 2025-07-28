#include <next.h>

Karich::Next::Next(std::vector<Middleware>& middlewares, Karich::Request& req, Karich::Response& res): 
    req_(req),
    res_(res),
    middlewares_(middlewares),
    index_(0)
{}

Karich::Next::Next(Next&& other):
    req_(other.req_),
    res_(other.res_),
    middlewares_(other.middlewares_),
    index_(other.index_)
{}

bool Karich::Next::operator() () {
    if (index_ < middlewares_.size()) {
        Middleware& current = middlewares_[index_++];
        current(req_, res_, *this);
    }

    return (index_ == middlewares_.size());
    
}