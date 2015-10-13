cmake_minimum_required (VERSION 2.6)
project (castle)
# The version number.
set (CASTLE_VERSION_MAJOR 1)
set (CASTLE_VERSION_MINOR 0)
set (CASTLE_DATASET "/temperature")
set (CMAKE_BUILD_TYPE Release)

set(CASTLE_TECHNOLOGY "cpp" CACHE STRING "Implementation technology chosen by the user at CMake configure time")
set_property(CACHE CASTLE_TECHNOLOGY PROPERTY STRINGS cpp cilk cuda opencl)
message(STATUS "Building '${CASTLE_TECHNOLOGY}' version")
if (${CASTLE_TECHNOLOGY} MATCHES "cpp")
  include_directories("${PROJECT_SOURCE_DIR}/cpp_deqn")
  add_subdirectory(cpp_deqn)
elseif(CASTLE_TECHNOLOGY MATCHES "cuda")
  include_directories("${PROJECT_SOURCE_DIR}/cuda_deqn")
  add_subdirectory(cuda_deqn)
else()
  message(FATAL_ERROR "Unsupported Technology: ${CASTLE_TECHNOLOGY}")
endif()
set(LINK_LIBS ${LINK_LIBS} deqn_lib)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/castle_config.h.in"
  "${PROJECT_BINARY_DIR}/castle_config.h"
)
 
# add the binary tree to the search path for include files
# so that we will find castle_config.h
include_directories("${PROJECT_BINARY_DIR}")
# Add the generic header directory
 
# Include HDF5
find_package(HDF5 COMPONENTS C HL)
include_directories(${HDF5_INCLUDE_DIR})
set(LINK_LIBS ${LINK_LIBS} ${HDF5_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("${PROJECT_SOURCE_DIR}/deqn")
# add the executable
file(GLOB CXX_SRCS *.cc)
file(GLOB CXX_HDRS *.h)
add_executable(castle ${CXX_SRCS} ${CXX_HDRS})
target_link_libraries(castle ${LINK_LIBS})
