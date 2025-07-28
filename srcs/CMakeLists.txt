find_package(Boost REQUIRED)

add_library(SRCS_FILES STATIC)
set(PROJECT_ROOT /home/tigran/Desktop/learn/http_cpp)

target_sources(SRCS_FILES PRIVATE
    controllers/get.cpp
    controllers/post.cpp
    middlewares/json_parse.cpp
    dotenv/dotenv.cpp
    dotenv/globals.cpp
)

add_subdirectory(http)

target_link_libraries(SRCS_FILES PRIVATE HTTP)

target_compile_definitions(SRCS_FILES PUBLIC PROJECT_ROOT=\"${PROJECT_ROOT}/\")
target_include_directories(SRCS_FILES PRIVATE ../includes)
target_include_directories(SRCS_FILES PRIVATE ${Boost_INCLUDE_DIRS})