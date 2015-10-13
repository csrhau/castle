cmake_minimum_required(VERSION 2.8)
find_package(CUDA REQUIRED)

set(CUDA_NVCC_FLAGS "-arch=compute_20 -code=sm_20,compute_20")

include_directories("${PROJECT_SOURCE_DIR}/deqn")

file(GLOB CXX_SRCS *.cc)
file(GLOB CUDA_SRCS *.cu)
file(GLOB CXX_HDRS *.h)
cuda_add_library(deqn_lib STATIC ${CXX_SRCS} ${CUDA_SRCS} ${CXX_HDRS})
