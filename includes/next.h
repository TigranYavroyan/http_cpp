#ifndef NEXT_HPP
#define NEXT_HPP

#include <includes.h>
#include <middleware.h>

class Next {
public:
    Next(std::vector<Middleware>& middlewares, Karich::Request& req, Karich::Response& res);
    Next(Next&& other);
    bool operator() ();
private:
    Karich::Request& req_;
    Karich::Response& res_;
    std::vector<Middleware>& middlewares_;
    std::size_t index_;
};

#endif // NEXT_HPP