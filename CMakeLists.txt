cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(boost_beast_http)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_ROOT "/home/tigran/Desktop/learn/http_cpp")

find_package(Boost REQUIRED)

add_subdirectory(srcs) # SRCS_FILES
add_executable(server server.cpp)
target_link_libraries(server PRIVATE SRCS_FILES)

target_compile_options(server PRIVATE "-DPROJECT_ROOT=\"${PROJECT_ROOT}/\"")
target_include_directories(server PRIVATE includes)
target_include_directories(server PRIVATE ${Boost_INCLUDE_DIRS})