#include "simulator.h"

#include <cstdlib>
#include <iostream>
#include <string>

#include "deqn.h"
#include "writer.h"

Simulator::Simulator(std::string infile_,
                     std::string prefix_,
                     int outrate_,
                     int timesteps_) : _input_file(infile_), 
                                       _writer(prefix_),
                                       _outrate(outrate_),
                                       _timesteps(timesteps_) {
  const size_t rows = _input_file.get_rows();
  const size_t cols = _input_file.get_cols();
  _u0 = static_cast<double *>(malloc(rows * cols * sizeof(double)));
  _u1 = static_cast<double *>(malloc(rows * cols * sizeof(double)));
  _input_file.populate_data(_u0);
}

Simulator::~Simulator() {
  free(_u0);
  free(_u1);
}

void Simulator::run() {
  // TODO - some kind of 'scheme' wrapper
  std::cout << "Simulator running!" << std::endl;
}
