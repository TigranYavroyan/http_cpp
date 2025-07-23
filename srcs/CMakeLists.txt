find_package(Boost REQUIRED)

add_library(SRCS_FILES STATIC)

target_sources(SRCS_FILES PRIVATE
    controllers/get.cpp
    controllers/post.cpp
    http/router/Router.cpp
    http/router/global_Router.cpp
    http/core/next.cpp
    http/core/middleware.cpp
    dotenv/dotenv.cpp
)

target_include_directories(SRCS_FILES PRIVATE ../includes)
target_include_directories(SRCS_FILES PRIVATE ${Boost_INCLUDE_DIRS})