#include <utils.h>

std::string_view Karich::utils::get_mime_type(const std::string& path) {
	static const std::unordered_map<std::string, std::string_view> mime_types = {
		{".html", "text/html"},
		{".htm", "text/html"},
		{".css", "text/css"},
		{".js", "application/javascript"},
		{".json", "application/json"},
		{".png", "image/png"},
		{".jpg", "image/jpeg"},
		{".jpeg", "image/jpeg"},
		{".gif", "image/gif"},
		{".svg", "image/svg+xml"},
		{".ico", "image/x-icon"},
		{".txt", "text/plain"},
		{".pdf", "application/pdf"},
		{".zip", "application/zip"},
		{".xml", "application/xml"},
	};

	size_t dot_pos = path.rfind('.');
	if (dot_pos != std::string::npos) {
		std::string ext = path.substr(dot_pos);
		auto it = mime_types.find(ext);
		if (it != mime_types.end()) {
			return it->second;
		}
	}
	return "application/octet-stream";
}