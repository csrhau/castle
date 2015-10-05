cmake_minimum_required (VERSION 2.6)
project (tutorial)
# The version number.
set (TUTORIAL_VERSION_MAJOR 1)
set (TUTORIAL_VERSION_MINOR 0)
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/tutorial_config.h.in"
  "${PROJECT_BINARY_DIR}/tutorial_config.h"
)
 
# add the binary tree to the search path for include files
# so that we will find tutorial_config.h
include_directories("${PROJECT_BINARY_DIR}")
 
# Add the CUDA kernels
include_directories("${PROJECT_SOURCE_DIR}/math_lib")
add_subdirectory(math_lib)


# add the executable
add_executable(tutorial tutorial.cc)
target_link_libraries(tutorial math_lib)
