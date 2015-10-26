cmake_minimum_required(VERSION 2.8)

include_directories("${PROJECT_SOURCE_DIR}/deqn_headers")

file(GLOB CXX_SRCS *.cc)
file(GLOB CXX_HDRS *.h)
add_library(deqn_lib STATIC ${CXX_SRCS} ${CXX_HDRS})
