#ifndef CASTLE_SIMULATOR_H
#define CASTLE_SIMULATOR_H

#include <string>

#include "input_file.h"
  
class Simulator {
  private:
    std::string _prefix;
    int _outrate;
    int _timestep;
    int _timesteps;
    int _rows;
    int _cols;
    double _nu;
    double _sigma;
    double _width;
    double _depth;
    double _initial_temp;
    double *_u0;
    double *_u1;

  public:
    Simulator(std::string infile_,
              std::string prefix_,
              int outrate, 
              int timesteps);

    ~Simulator();
    int get_xmin() const;
    int get_ymin() const;
    int get_xmax() const;
    int get_ymax() const;
    double get_nu() const;
    double get_sigma() const;
    double get_width() const;
    double get_depth() const;
    double get_temperature() const;
    const double * get_u0() const;
    const double * get_u1() const;
    void run();
  private:
    void step();
    void diffuse(); 
    void reflect();
    void persist();
};

#endif
