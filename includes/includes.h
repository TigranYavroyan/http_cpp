#ifndef INCLUDES_HPP
#define INCLUDES_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <dotenv.h>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;
using json = nlohmann::json;

using Request  = boost::beast::http::request<boost::beast::http::string_body>;
using Response = boost::beast::http::response<boost::beast::http::string_body>;
using Handler  = std::function<void(const Request&, Response&)>;

#endif // INCLUDES_HPP