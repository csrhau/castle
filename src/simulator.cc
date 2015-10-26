#include "simulator.h"

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>

#include "deqn.h"
#include "fpcompare.h"

#define BORDER 1 
#define INDEX2D(row, col, rows, cols) ((row) * (cols) + (col))

Simulator::Simulator(std::string infile_,
                     std::string prefix_,
                     int outrate_,
                     int timesteps_) : _prefix(prefix_),
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
  _initial_temp = get_temperature();  
  reflect(); // Ensure the boundary layer is reflected at ts 0 
}

Simulator::~Simulator() {
  free(_u0);
  free(_u1);
}

int Simulator::get_xmin() const { return BORDER; }
int Simulator::get_ymin() const { return BORDER; }
int Simulator::get_xmax() const { return _cols - 2 * BORDER; }
int Simulator::get_ymax() const { return _rows - 2 * BORDER; }
double Simulator::get_nu() const { return _nu; }
double Simulator::get_sigma() const { return _sigma; }
double Simulator::get_width() const { return _width; }
double Simulator::get_depth() const { return _depth; }
const double * Simulator::get_u0() const { return _u0; }
const double * Simulator::get_u1() const { return _u1; }

double Simulator::get_temperature() const {
  double temp = 0;
  for (int i = get_ymin(); i < get_ymax(); ++i) {
    for (int j = get_xmin(); j < get_xmax(); ++j) {
      int offset = INDEX2D(i, j, _rows, _cols);
      temp += _u0[offset];
    }
  }
  return temp;
}

void Simulator::run() {
  while (_timestep < _timesteps) {
    step();
    ++_timestep;
    double new_temp = get_temperature();
    if (Tools::DoubleCompare::not_equal(_initial_temp, new_temp)) {
      std::cerr << "WARNING! Temperature divergence detected after step "
                << _timestep << ". Initial temperature: " << _initial_temp
                << ", Current temperature: " << new_temp << ", delta: "
                << (new_temp - _initial_temp) << std::endl;
    }
    if (_timestep % _outrate == 0) {
      persist();
    }
  }
  // Persist final state only if not done above.
  if (_timestep % _outrate != 0) {
    persist();
  }
}

void Simulator::step() {
  diffuse();
  reflect();
  std::swap(_u0, _u1);
}

void Simulator::diffuse() {
  std::cout << "Simulator diffusing!"<< std::endl;
}

void Simulator::reflect() {
  std::cout << "Simulator reflecting!"<< std::endl;
}

void Simulator::persist() {
  std::cout << "Simulator persisting output to file:"
            << _prefix << "_" << _timestep << ".h5" << std::endl;
}
