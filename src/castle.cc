#include <stdlib.h>
#include <iostream>

#include "mymath.h"
#include "castle_config.h"

int main(int argc, char *argv[]) {
  std::cout << argv[0] << " Version: " << CASTLE_VERSION_MAJOR << '.' << CASTLE_VERSION_MINOR << std::endl;
  foosay();
  return EXIT_SUCCESS;
}
