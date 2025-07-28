#ifndef UTILS_HPP
#define UTILS_HPP

#include <includes.h>
#include <request.h>
#include <response.h>

namespace Karich::utils {
	std::string_view get_mime_type(const std::string& path);

	template <typename T, typename Callable, typename... Args>
	std::pair<int64_t, T> time_calculate (Callable c, Args&&... args);

}

template <typename T, typename Callable, typename... Args>
std::pair<int64_t, T> Karich::utils::time_calculate (Callable c, Args&&... args) {
	auto start = std::chrono::high_resolution_clock::now();
	T res = c(std::forward<Args>(args)...);
	auto end = std::chrono::high_resolution_clock::now();
	return {std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(), res};
}

#endif // UTILS_HPP