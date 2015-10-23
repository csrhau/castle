#include "deqn.h"

#include <iostream>

#include "deqn_impl.h"

void Deqn::say_hi() const {
  std::cout << "hi from cpp deqn object!" << std::endl;
}

void Deqn::advance() {
  std::cout << "DEQN code advancing" << std::endl;
}

/*

void Deqn::diffuse(int rows,
                   int cols,
                   double cx,
                   double cy,
                   double *u0,
                   double *u1) {
    // Central points
    for (int i = 1; i < rows-1; ++i) {
      for (int j = 1; j < cols-1; ++j) {
        const size_t center = INDEX2D(i, j, rows, cols);
        const size_t north = INDEX2D(i-1, j, rows, cols);
        const size_t west = INDEX2D(i, j-1, rows, cols);
        const size_t south = INDEX2D(i+1, j, rows, cols);
        const size_t east = INDEX2D(i, j+1, rows, cols);
        u1[center] = u0[center] 
          + cx * (u0[west] - 2 * u0[center] + u0[east]) 
          + cy * (u0[north] - 2 * u0[center] + u0[south]);
      }
    }
    // Reflect Boundaries
    // TOP
    for (int j = 0; j < cols; ++j) {
      const size_t top_outer = INDEX2D(0, j, rows, cols);
      const size_t top_inner = INDEX2D(1, j, rows, cols);
      u1[top_outer] = u1[top_inner];
    }
    // LEFT
    for (int i = 1; i < rows-1; ++i) {
      const size_t left_outer = INDEX2D(i, 0, rows, cols);
      const size_t left_inner = INDEX2D(i, 1, rows, cols);
      u1[left_outer] = u1[left_inner];
    }
    // BOTTOM
    for (int j = 0; j < cols; ++j) {
      const size_t bottom_outer = INDEX2D(rows-1, j, rows, cols);
      const size_t bottom_inner = INDEX2D(rows-2, j, rows, cols);
      u1[bottom_outer] = u1[bottom_inner];
    }
    // RIGHT
    for (int i = 1; i < rows-1; ++i) {
      const size_t right_outer = INDEX2D(i, cols-1, rows, cols);
      const size_t right_inner = INDEX2D(i, cols-2, rows, cols);
      u1[right_outer] = u1[right_inner];
    }
}
*/
