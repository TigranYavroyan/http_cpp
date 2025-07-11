cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(boost_beast_http)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_FILES srcs/global_Router.cpp srcs/Router.cpp)
set(SERVER server.cpp)

add_library(router STATIC ${SRC_FILES})
target_include_directories(router PRIVATE includes ${Boost_INCLUDE_DIRS})

find_package(Boost REQUIRED)

add_executable(server ${SERVER})
target_link_libraries(server router)
target_include_directories(server PRIVATE ${Boost_INCLUDE_DIRS} includes)