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
#include <memory>
#include <list>
#include <optional>
#include <filesystem>
#include <dotenv.h>

extern std::string project_root;

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace fs = std::filesystem;
using tcp = net::ip::tcp;
using json = nlohmann::json;

namespace Karich {
	class Request;
	class Response;
}

using BeastReq = beast::http::request<beast::http::string_body>;
using BeastRes = beast::http::response<beast::http::string_body>;
using Handler  = std::function<void(Karich::Request&, Karich::Response&)>;

#endif // INCLUDES_HPP