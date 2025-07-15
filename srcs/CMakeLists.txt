find_package(Boost REQUIRED)

add_library(SRCS_FILES STATIC)

target_sources(SRCS_FILES PRIVATE
    controllers/get.cpp
    controllers/post.cpp
    router/Router.cpp
    router/global_Router.cpp
)

target_include_directories(SRCS_FILES PRIVATE ../includes)
target_include_directories(SRCS_FILES PRIVATE ${Boost_INCLUDE_DIRS})