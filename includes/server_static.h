#ifndef SERVER_STATIC_HPP
#define SERVER_STATIC_HPP

#include <filesystem>
#include <fstream>
#include <includes.h>
#include <request.h>
#include <response.h>
#include <next.h>

void serve_static(Request& req, Response& res);

#endif // SERVER_STATIC_HPP