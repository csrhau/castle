#include <stdlib.h>
#include <iostream>
#include <chrono>

#include "mymath.h"
#include "castle_config.h"







int main(int argc, char *argv[]) {
  using namespace std::chrono;
  std::cout << argv[0] << " Version: " << CASTLE_VERSION_MAJOR << '.' << CASTLE_VERSION_MINOR << std::endl;
  steady_clock::time_point t_start = steady_clock::now();
  foosay();
  steady_clock::time_point t_end = steady_clock::now();
  duration<double> runtime = duration_cast<duration<double>>(t_end - t_start);
  std::cout << "Runtime: " << runtime.count() << " seconds." << std::endl;
  return EXIT_SUCCESS;
} // namespace hostonly
