#include "simulator.h"

#include <cstdlib>
#include <iostream>
#include <string>

#include "deqn.h"
#include "writer.h"

Simulator::Simulator(std::string infile_,
                     std::string prefix_,
                     int outrate_,
                     int timesteps_) : _writer(prefix_),
                                       _outrate(outrate_),
                                       _timesteps(timesteps_) {
  InputFile input_file(infile_);
  _rows = input_file.get_rows();
  _cols = input_file.get_cols();
  _width = input_file.get_width();
  _depth = input_file.get_depth();
  _sigma = input_file.get_sigma();
  _nu = input_file.get_nu();
  _u0 = static_cast<double *>(malloc(_rows * _cols * sizeof(double)));
  _u1 = static_cast<double *>(malloc(_rows * _cols * sizeof(double)));
  input_file.populate_data(_u0);
}

Simulator::~Simulator() {
  free(_u0);
  free(_u1);
}

int Simulator::get_rows() const { return _rows; }
int Simulator::get_cols() const { return _cols; }
double Simulator::get_nu() const { return _nu; }
double Simulator::get_sigma() const { return _sigma; }
double Simulator::get_width() const { return _width; }
double Simulator::get_depth() const { return _depth; }
const double * Simulator::get_u0() const { return _u0; }
const double * Simulator::get_u1() const { return _u1; }

void Simulator::diffuse() {
  std::cout << "Simulator diffusing!"<< std::endl;
}

void Simulator::run() {
  // TODO - some kind of 'scheme' wrapper
  std::cout << "Simulator running!" << std::endl;
  diffuse();
}
