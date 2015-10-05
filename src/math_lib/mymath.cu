#include "mymath.h"

#include <stdio.h>

__global__ void helloCUDA(float f) {
  printf("Hello world from thread %d with value %f\n", threadIdx.x, f);
}

void foosay(void) {
  printf("Foo-ing\n");
  helloCUDA<<<1, 5>>>(1.2345f);
  printf("Code: %d wanted %d\n", cudaGetLastError(), 0);
  printf("Code: %d wanted %d\n", cudaDeviceSynchronize(), 0);
  printf("Foo-ed\n");
  cudaDeviceReset();
}
