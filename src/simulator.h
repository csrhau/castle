#ifndef CASTLE_SIMULATOR_H
#define CASTLE_SIMULATOR_H

#include <string>

#include "input_file.h"
#include "writer.h"
  
class Simulator {
  private:
    InputFile _input_file;
    Writer _writer;
    int _outrate;
    int _timesteps;
    double *_u0;
    double *_u1;

  public:
    Simulator(std::string infile_,
             std::string prefix_,
             int outrate, 
             int timesteps);

    ~Simulator();
    void run();
};

#endif
