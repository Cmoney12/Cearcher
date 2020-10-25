cmake_minimum_required(VERSION 3.17)
project(untitled5)

set(CMAKE_CXX_STANDARD 14)
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)
add_executable (untitled5 main.cpp)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(untitled5 ${CURL_LIBRARIES})
