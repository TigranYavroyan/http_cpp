cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(boost_beast_http)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)

add_subdirectory(srcs) # SRCS_FILES
add_subdirectory(utils) # UTILS
add_executable(server server.cpp)
target_link_libraries(server PRIVATE SRCS_FILES UTILS)

target_include_directories(server PRIVATE includes)
target_include_directories(server PRIVATE ${Boost_INCLUDE_DIRS})