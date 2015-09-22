cmake_minimum_required (VERSION 2.6)
project (castle)
# Version numbers
set (CASTLE_VERSION_MAJOR 1)
set (CASTLE_VERSION_MINOR 0)

# Configure a header to pass through the version settings
configure_file(
  "${PROJECT_SOURCE_DIR}/castle_config.h.in"
  "${PROJECT_BINARY_DIR}/castle_config.h"
)

# Add the binary tree to the includes path to find generated headers
include_directories("${PROJECT_BINARY_DIR}")

add_executable(castle main.cc)
