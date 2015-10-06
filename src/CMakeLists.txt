cmake_minimum_required (VERSION 2.6)
project (castle)
# The version number.
set (CASTLE_VERSION_MAJOR 1)
set (CASTLE_VERSION_MINOR 0)
set (CASTLE_DATASET "/temperature")
set (CMAKE_BUILD_TYPE Release)
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/castle_config.h.in"
  "${PROJECT_BINARY_DIR}/castle_config.h"
)
 
# add the binary tree to the search path for include files
# so that we will find castle_config.h
include_directories("${PROJECT_BINARY_DIR}")
 
# Include HDF5
find_package(HDF5 COMPONENTS C HL)
include_directories(${HDF5_INCLUDE_DIR})
set(LINK_LIBS ${LINK_LIBS} ${HDF5_LIBRARIES})

# Add the CUDA kernels
include_directories("${PROJECT_SOURCE_DIR}/math_lib")
add_subdirectory(math_lib)
set(LINK_LIBS ${LINK_LIBS} math_lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# add the executable
add_executable(castle castle.cc)
target_link_libraries(castle ${LINK_LIBS})
