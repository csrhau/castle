#include "deqn.h"

#include <iostream>

Deqn::Deqn() {}
Deqn::~Deqn() {}
void Deqn::initialize() {}

void Deqn::say_hi() const {
  std::cout << "hi from cuda deqn object!" << std::endl;
}

void Deqn::advance() {
  std::cout << "DEQN code advancing" << std::endl;
}
