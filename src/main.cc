#include <iostream>
#include <algorithm>

#include "grid.h"
#include "castle_config.h"


#define SIM_ROWS 31
#define SIM_COLS 31
#define STENCIL_RADIUS 1 
#define TIME_STEPS 10

int main(int argc, char *argv[]) {
  std::cout << "Castle " << CASTLE_VERSION_MAJOR << CASTLE_VERSION_MINOR << std::endl;

  double **u0 = new double*[SIM_ROWS];
  double **u1 = new double*[SIM_ROWS];

  // Array notation doesn't work for this allocation
  for (int r = 0; r < SIM_ROWS; ++r) {
    u0[r] = new double[SIM_COLS];
    u1[r] = new double[SIM_COLS];
  }

  std::cout << u0[0] << std::endl;
  std::cout << u0[1] << std::endl;
  std::cout << u0[2] << std::endl;

  size_t row_y = STENCIL_RADIUS;
  size_t rows = SIM_ROWS - 2*STENCIL_RADIUS;
  size_t col_x = STENCIL_RADIUS;
  size_t cols = SIM_COLS - 2*STENCIL_RADIUS;



  // Initialize
  u0[0:SIM_ROWS][0:SIM_COLS] = 1.0;
  u1[0:SIM_ROWS][0:SIM_COLS] = 1.0;


  double vis = 1;
  double dx = 2.0 / (SIM_COLS-1);
  double dy = 2.0 / (SIM_ROWS-1);
  double nu = 0.05;
  double sigma = 0.25;
  double dt = sigma * dx * dy / nu;

  double cx = vis*dt/(dx*dx);
  double cy = vis*dt/(dy*dy);

  double tNext, tNow = __sec_reduce_add(u0[0:SIM_ROWS][0:SIM_COLS]);
  std::cout << "Starting..." << std::endl;
  for (size_t ts = 0; ts < TIME_STEPS; ++ts) {
    // Diffusion Equation
    u1[row_y:rows][col_x:cols] = u0[row_y:rows][col_x:cols]       // x,y 
                               + cx*u0[row_y:rows][col_x-1:cols]  // x-1,y
                               + cx*u0[row_y:rows][col_x+1:cols]  // x+1,y
                               + cy*u0[row_y-1:rows][col_x:cols]  // x,y-1
                               + cy*u0[row_y+1:rows][col_x:cols]; // x,y+1



    // Reflect Boundaries
    u1[0][0:SIM_COLS] = u1[1][0:SIM_COLS];
    u1[SIM_ROWS-1][0:SIM_COLS] = u1[SIM_ROWS-2][0:SIM_COLS];
    u1[0:SIM_ROWS][0] = u1[0:SIM_ROWS][1];
    u1[0:SIM_ROWS][SIM_COLS-1] = u1[0:SIM_ROWS][SIM_COLS-2];



    // TODO: REFLECT BOUNDARIES

    std::swap(u0, u1);


    tNext =  __sec_reduce_add(u0[0:SIM_ROWS][0:SIM_COLS]);
    std::cout << "Timestep: " << ts << "start temp:" << tNow 
                                    << "new temp:" << tNext << std::endl;
    tNow = tNext;
  }
  Grid<RowExchangePolicy> g;
  g.step();

  delete[] u0[0:SIM_ROWS];
  delete[] u1[0:SIM_ROWS];
  delete[] u1;
  delete[] u0;
}

// Shifting:
// std::cout << "\nShifted Retrograde\n";
// u1[0:9][0:9] = u0[1:9][1:9];
