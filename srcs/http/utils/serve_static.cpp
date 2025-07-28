#include <utils.h>

void Karich::utils::serve_static(Karich::Request& req, Karich::Response& res) {
    std::string base_path = project_root + "public";
    std::string url_path = req.url();

    if (url_path == "/")
        url_path = "/index.html";

    std::string file_path = base_path + url_path;

    if (!std::filesystem::exists(file_path)) {
        return;  // not found? try next handler
    }

    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        res.send("Failed to open file").status(500);
        return;
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());

    // Set content-type based on file extension (simple map)
    if (file_path.ends_with(".html"))
        res.set_header("Content-Type", "text/html");
    else if (file_path.ends_with(".css"))
        res.set_header("Content-Type", "text/css");
    else if (file_path.ends_with(".js"))
        res.set_header("Content-Type", "application/javascript");
    else if (file_path.ends_with(".png"))
        res.set_header("Content-Type", "image/png");
    else
        res.set_header("Content-Type", "application/octet-stream");

    res.send(content).status(200);
}
