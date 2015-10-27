#include "simulator.h"

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include "deqn.h"
#include "fpcompare.h"
#include "castle_config.h"

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

  // TODO - isn't nu redundant??
  const double dx = _width / _cols;
  const double dy = _depth / _rows;
  const double dt = _sigma * dx * dy / _nu;
  _cx = _nu * dt / (dx * dx);
  _cy = _nu * dt / (dy * dy); 

  std::cout << "CX: " << _cx << " CY: " << _cy << std::endl;
  _u0 = static_cast<double *>(malloc(_rows * _cols * sizeof(double)));
  _u1 = static_cast<double *>(malloc(_rows * _cols * sizeof(double)));
  input_file.populate_data(_u1);
  // Ensure the boundary layer is reflected at ts 0 
  reflect();   
  std::swap(_u0, _u1);
  _initial_temp = get_temperature();  
}

Simulator::~Simulator() {
  free(_u0);
  free(_u1);
}

int Simulator::get_xmin() const { return BORDER; }
int Simulator::get_ymin() const { return BORDER; }
int Simulator::get_xmax() const { return _cols - BORDER; }
int Simulator::get_ymax() const { return _rows - BORDER; }
double Simulator::get_nu() const { return _nu; }
double Simulator::get_sigma() const { return _sigma; }
double Simulator::get_width() const { return _width; }
double Simulator::get_depth() const { return _depth; }
const double * Simulator::get_u0() const { return _u0; }
const double * Simulator::get_u1() const { return _u1; }
  
double Simulator::get_temperature() const {
  // Calculate temp
  double temperature = 0;
  for (int i = get_ymin(); i < get_ymax(); ++i) {
    for (int j = get_ymin(); j < get_ymax(); ++j) {
      const size_t center = INDEX2D(i, j, _rows, _cols);
      temperature += _u0[center];
    }
  }
  return temperature;
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
  for (int i = get_ymin(); i < get_ymax(); ++i) {
    for (int j = get_xmin(); j < get_ymax(); ++j) {
      const int center = INDEX2D(i, j, _rows, _cols);
      const int north = INDEX2D(i-1, j, _rows, _cols);
      const int west = INDEX2D(i, j-1, _rows, _cols);
      const int south = INDEX2D(i+1, j, _rows, _cols);
      const int east = INDEX2D(i, j+1, _rows, _cols);
      _u1[center] = _u0[center] 
                  + _cx * (_u0[west] - 2 * _u0[center] + _u0[east]) 
                  + _cy * (_u0[north] - 2 * _u0[center] + _u0[south]);
    }
  }
}

void Simulator::reflect() {
  // Horizontal (top/bottom) boundaries
  for (int j = get_xmin(); j < get_ymax(); ++j) {
    // Top
    const size_t top_outer = INDEX2D(get_ymin() - BORDER, j, _rows, _cols);
    const size_t top_inner = INDEX2D(get_ymin(), j, _rows, _cols);
    _u1[top_outer] = _u1[top_inner];
    // Bottom
    const size_t bottom_outer = INDEX2D(get_ymax() + BORDER, j, _rows, _cols);
    const size_t bottom_inner = INDEX2D(get_ymax(), j, _rows, _cols);
    _u1[bottom_outer] = _u1[bottom_inner];
  }
  // Vertical (Left/Right) boundaries
  for (int i = get_ymin(); i < get_ymax(); ++i) {
    // Left
    const size_t left_outer = INDEX2D(i, get_xmin() - BORDER, _rows, _cols);
    const size_t left_inner = INDEX2D(i, get_xmin(), _rows, _cols);
    _u1[left_outer] = _u1[left_inner];
    // Right
    const size_t right_outer = INDEX2D(i, get_xmax() + BORDER, _rows, _cols);
    const size_t right_inner = INDEX2D(i, get_xmax() , _rows, _cols);
    _u1[right_outer] = _u1[right_inner];
  }
}

void Simulator::persist() {
  std::stringstream namer;
  namer << _prefix << "_" << _timestep << ".h5";
  std::cout << "Simulator persisting output to file: " 
            << namer.str() << std::endl;
}
