#include <iostream>
#include <algorithm>

#include "grid.h"
#include "castle_config.h"


#define SIM_ROWS 100000
#define SIM_COLS 100000
#define STENCIL_RADIUS 1 
#define TIME_STEPS 10

int main(int argc, char *argv[]) {
  std::cout << "Castle " << CASTLE_VERSION_MAJOR << CASTLE_VERSION_MINOR << std::endl;



  double **u0 = new double*[SIM_ROWS];
  u0[0:SIM_ROWS] = new double[SIM_COLS];

  double **u1 = new double*[SIM_ROWS];
  u1[0:SIM_ROWS] = new double[SIM_COLS];



  size_t row = STENCIL_RADIUS;
  size_t rows = SIM_ROWS - 2*STENCIL_RADIUS;
  size_t col = STENCIL_RADIUS;
  size_t cols = SIM_COLS - 2*STENCIL_RADIUS;


  double tNext, tNow = __sec_reduce_add(u0[0:SIM_ROWS][0:SIM_COLS]);
  std::cout << "Starting..." << std::endl;
  for (size_t ts = 0; ts < TIME_STEPS; ++ts) {
    // Diffusion Equation
    u1[row:rows][col:cols] = u0[row:rows][col:cols] 
                           + u0[row-1:rows][col:cols]
                           + u0[row+1:rows][col:cols]
                           + u0[row:rows][col-1:cols]
                           + u0[row:rows][col+1:cols];
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


}

// Shifting:
// std::cout << "\nShifted Retrograde\n";
// u1[0:9][0:9] = u0[1:9][1:9];
