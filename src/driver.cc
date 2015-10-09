#include "driver.h"

#include <iostream>
#include <string>


#include "mymath.h"
#include "writer.h"


Driver::Driver(std::string prefix_) : _writer(prefix_) {
  

}

Driver::~Driver() {

}

void Driver::run() {

  for (int step = 0; step < 10; ++step) {
    std::cout << "Doing step" << step << std::endl;
    _writer.write();
  }

  foosay();
}
