#ifndef IS_MIDDLEWARE_HPP
#define IS_MIDDLEWARE_HPP

#include <type_traits>
#include <middleware.h>

namespace Karich {
    template <typename T>
    constexpr bool is_middleware_like_v = std::is_invocable_r_v<
        void, T, Request&, Response&, Next&
    >;
    
    template <typename... Mids>
    struct are_all_middlewares : std::bool_constant<(is_middleware_like_v<Mids> && ...)> {};
    
    template <typename... Mids>
    constexpr bool are_all_middlewares_v = are_all_middlewares<Mids...>::value;
}


#endif // IS_MIDDLEWARE_HPP