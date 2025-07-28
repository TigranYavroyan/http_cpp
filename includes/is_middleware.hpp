#ifndef IS_MIDDLEWARE_HPP
#define IS_MIDDLEWARE_HPP

#include <type_traits>
#include <middleware.h>

template <typename T>
struct is_valid_middleware_type : std::false_type {};

template <>
struct is_valid_middleware_type<Karich::Middleware> : std::true_type {};

template <>
struct is_valid_middleware_type<Karich::MiddlewareFunc> : std::true_type {};

template <>
struct is_valid_middleware_type<Karich::MiddlewareFuncPtr> : std::true_type {};

template <typename T>
constexpr bool is_valid_middleware_v = is_valid_middleware_type<T>::value;

template <typename... Mids>
struct are_all_middlewares : std::conjunction<is_valid_middleware_type<Mids>...> {};

template <typename... Mids>
constexpr bool are_all_middlewares_v = are_all_middlewares<Mids...>::value;

#endif // IS_MIDDLEWARE_HPP