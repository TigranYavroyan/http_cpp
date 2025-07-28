#ifndef GET_HPP
#define GET_HPP

#include <includes.h>
#include <request.h>
#include <response.h>

void root (Karich::Request& req, Karich::Response& res);
void index_html (Karich::Request& req, Karich::Response& res);

#endif // GET_HPP