#include "mymath.h"

#include <iostream>

#include "deqn.h"

void foosay(void) {
  std::cout << " Hello from a strictly c++ implementation!" << std::endl;
  Deqn d;
  d.say_hi();
}
