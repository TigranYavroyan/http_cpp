find_package(Boost REQUIRED)

add_library(HTTP STATIC)

target_sources(HTTP PRIVATE
	utils/get_mime_type.cpp
	utils/serve_static.cpp
    router/router.cpp
    core/next.cpp
    core/middleware.cpp
    core/middleware.cpp
    core/request.cpp
    core/response.cpp
    core/http_server.cpp
)

target_include_directories(HTTP PRIVATE ../../includes/)
target_include_directories(HTTP PRIVATE ${Boost_INCLUDE_DIRS})