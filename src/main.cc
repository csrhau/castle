#include <iostream>
#include <algorithm>

#include <stdlib.h>
#include<cilk/cilk.h>

#include "grid.h"
#include "castle_config.h"

int main(int argc, char *argv[]) {
  std::cout << "Castle v" << CASTLE_VERSION_MAJOR << CASTLE_VERSION_MINOR 
            << "\nSimulating a " << NX << "x" << NY << " domain." << std::endl; 

  // Define values
  const size_t nx = NX;
  const size_t ny = NY;
  const size_t nt = NT;
  const double nu = NU;
  const double sigma = SG;
  const double dx = XD/(nx - 1.0);
  const double dy = YD/(ny - 1.0);
  const double dt = sigma * dx * dy / nu;

  // Allocate space for simulation
  double **u0 = new double*[ny];
  double **u1 = new double*[ny];
  for (int r = 0; r < ny; ++r) {
    u0[r] = new double[nx];
    u1[r] = new double[nx];
  }

  // Initialize space
  u0[0:ny][0:nx] = 1.0;
  u0[ny/4:ny/2][nx/4:nx/2] = 2.0;

  // Calculate initial temperature
  const double tInit = __sec_reduce_add(u0[1:ny-2][1:nx-2*1]);
  std::cout << "Initial temperature: " << tInit << std::endl;

  const double cx = nu * dt / (dx * dx);
  const double cy = nu * dt / (dy * dy); 

  for (size_t t = 0; t < nt; ++t) {
#if defined(CILK_PAR)
    cilk_for (size_t r = 1; r < ny - 1; ++r) {
      u1[r][1:nx-2] = u0[r][1:nx-2] 
                                 + cx * (u0[r][0:nx-2] 
                                      - 2 * u0[r][1:nx-2] 
                                      + u0[r][2:nx-2])
                                 + cy * (u0[r-1][1:nx-2] 
                                      - 2 * u0[r][1:nx-2] 
                                      + u0[r+1][1*1:nx-2]);
    }
#else
    u1[1:ny-2][1:nx-2] = u0[1:ny-2][1:nx-2] 
                               + cx * (u0[1:ny-2][0:nx-2] 
                                    - 2 * u0[1:ny-2][1:nx-2] 
                                    + u0[1:ny-2][2:nx-2])
                               + cy * (u0[0:ny-2][1:nx-2] 
                                    - 2 * u0[1:ny-2][1:nx-2] 
                                    + u0[2:ny-2][1*1:nx-2]);
#endif
    // Reflect Boundaries TODO: consider stencil radius
    u1[0][0:nx] = u1[1][0:nx];
    u1[ny-1][0:nx] = u1[ny-2][0:nx];
    u1[0:ny][0] = u1[0:ny][1];
    u1[0:ny][nx-1] = u1[0:ny][nx-2];

    // Update state
    std::swap(u0, u1);
    if (t % 128 == 0) {
      const double tNow = __sec_reduce_add(u0[1:ny-2][1:nx-2]);
      std::cout << "ts " << t << " temp: " << tNow << std::endl;
    }
  }

  // De-allocate space for simulation
  delete[] u0[0:ny]; 
  delete[] u1[0:ny]; 
  delete[] u0;
  delete[] u1;
  return EXIT_SUCCESS;
}
