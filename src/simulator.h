#ifndef CASTLE_SIMULATOR_H
#define CASTLE_SIMULATOR_H

#include <string>

#include "input_file.h"
#include "writer.h"
  
class Simulator {
  private:
    Writer _writer;
    int _outrate;
    int _timesteps;
    int _rows;
    int _cols;
    double _nu;
    double _sigma;
    double _width;
    double _depth;
    double *_u0;
    double *_u1;

  public:
    Simulator(std::string infile_,
             std::string prefix_,
             int outrate, 
             int timesteps);

    ~Simulator();
    int get_rows() const;
    int get_cols() const;
    double get_nu() const;
    double get_sigma() const;
    double get_width() const;
    double get_depth() const;
    const double * get_u0() const;
    const double * get_u1() const;
    void run();
  private:
    void diffuse(); 
};

#endif
