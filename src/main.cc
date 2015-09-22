#include <iostream>

#include "castle_config.h"

void print_int(int printme) {
  std::cout << printme << std::endl;
}

int main(int argc, char *argv[]) {
  int a[10];
  a[:] = 42;
  print_int(a[:]);
  std::cout << "Castle " << CASTLE_VERSION_MAJOR << CASTLE_VERSION_MINOR << std::endl;
}
