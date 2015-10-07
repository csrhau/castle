cmake_minimum_required(VERSION 2.8)
find_package(CUDA REQUIRED)

set(CUDA_NVCC_FLAGS "-arch=compute_20 -code=sm_20,compute_20")

cuda_add_library(deqn_lib STATIC mymath.cu mymath.h)
