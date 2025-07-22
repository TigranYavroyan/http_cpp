#ifndef NEXT_HPP
#define NEXT_HPP

#include <includes.h>
#include <middleware.hpp>

class Next {
public:
    Next(std::vector<Middleware>& middlewares, Request& req, Response& res): 
        req_(req),
        res_(res),
        middlewares_(middlewares),
        index_(0)
    {}

    Next(Next&& other):
        req_(other.req_),
        res_(other.res_),
        middlewares_(other.middlewares_),
        index_(other.index_)
    {}

    void operator() () {
        if (index_ < middlewares_.size()) {
            Middleware& current = middlewares_[index_++];
            current(req_, res_, *this);
        }
    }
private:
    Request& req_;
    Response& res_;
    std::vector<Middleware>& middlewares_;
    std::size_t index_;
};

#endif // NEXT_HPP