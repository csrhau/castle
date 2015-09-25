cmake_minimum_required (VERSION 2.8)
project (castle)
# Version numbers
set (CASTLE_VERSION_MAJOR 1)
set (CASTLE_VERSION_MINOR 0)
set(CMAKE_BUILD_TYPE Release)


# Simulation Parameters
set(XD 2 CACHE STRING "Magnitude of X Dimension")
set(YD 2 CACHE STRING "Magnitude of Y Dimension")
set(NX 31 CACHE STRING "Cells in the X Dimension")
set(NY 31 CACHE STRING "Cells in the Y Dimension")
set(NT 30 CACHE STRING "Simulation Timesteps")
set(NU 0.05 CACHE STRING "Coefficient of Diffusivity")
set(SG 0.25 CACHE STRING "Sigma")
option (CILK_PAR "Parallelize with cilk" ON)

# Configure a header to pass through the version settings
configure_file(
  "${PROJECT_SOURCE_DIR}/castle_config.h.in"
  "${PROJECT_BINARY_DIR}/castle_config.h"
)

# Add the binary tree to the includes path to find generated headers
include_directories("${PROJECT_BINARY_DIR}")

# Include grid code
include_directories("${PROJECT_SOURCE_DIR}/grid")
add_subdirectory(grid)

add_executable(castle main.cc)
target_link_libraries(castle grid)
