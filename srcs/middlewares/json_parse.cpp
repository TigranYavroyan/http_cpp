#include <json_parse.h>

void json_parser (Request& req, Response& res, Next& next) {
    if (req.method() == "GET")
        next();
    else {
        try {
            BeastReq& raw = req.raw();
            json parsed_body = json::parse(raw.body());
            req.set_body(parsed_body);
            next();
        } catch (const nlohmann::json::parse_error& e) {
            std::cerr << e.what() << std::endl;
            std::cout << "Error from json parsing" << std::endl;
        }
    }
}