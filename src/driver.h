#ifndef CASTLE_DRIVER_H
#define CASTLE_DRIVER_H

#include <string>

#include "writer.h"

  
class Driver {
  private:
    Writer _writer;

  public:
    Driver(std::string prefix_);
    ~Driver();
    void run();
};

#endif
