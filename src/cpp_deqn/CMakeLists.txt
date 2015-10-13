cmake_minimum_required(VERSION 2.8)

include_directories("${PROJECT_SOURCE_DIR}/deqn")

add_library(deqn_lib STATIC deqn.cc)
