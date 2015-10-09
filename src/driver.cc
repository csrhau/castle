#include "driver.h"

#include <iostream>
#include <string>

#include "mymath.h"
#include "deqn.h"
#include "writer.h"

Driver::Driver(std::string prefix_) : _writer(prefix_) {
  

}

Driver::~Driver() {

}

void Driver::run() {
  Deqn d;

  for (int step = 0; step < 10; ++step) {
    std::cout << "Doing step" << step << std::endl;
    _writer.write();
    d.say_hi();
  }

  foosay();
}
