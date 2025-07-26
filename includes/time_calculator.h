#ifndef TIME_CALCULATOR_HPP
#define TIME_CALCULATOR_HPP

#include <includes.h>

template <typename T, typename Callable, typename... Args>
inline std::pair<int64_t, T> time_calculate (Callable c, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    T res = c(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    return {std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(), res};
}

#endif // TIME_CALCULATOR_HPP