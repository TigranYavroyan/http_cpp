find_package(Boost REQUIRED)

add_library(SRCS_FILES STATIC)


target_sources(SRCS_FILES PRIVATE
    controllers/get.cpp
    controllers/post.cpp
    middlewares/json_parse.cpp
    dotenv/dotenv.cpp
    dotenv/glob_variable.cpp
)

add_subdirectory(http)

target_link_libraries(SRCS_FILES PRIVATE HTTP)

target_include_directories(SRCS_FILES PRIVATE ../includes)
target_include_directories(SRCS_FILES PRIVATE ${Boost_INCLUDE_DIRS})