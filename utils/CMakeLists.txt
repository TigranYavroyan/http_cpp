find_package(Boost REQUIRED)

add_library(UTILS STATIC)
target_sources(UTILS PRIVATE
    handle_session.cpp
)

target_include_directories(UTILS PRIVATE ../includes)
target_include_directories(UTILS PRIVATE ${Boost_INCLUDE_DIRS})