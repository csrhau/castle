#include <stdlib.h>
#include <iostream>

#include "mymath.h"
#include "tutorial_config.h"

int main(int argc, char *argv[]) {
  std::cout << argv[0] << " Version: " << TUTORIAL_VERSION_MAJOR << '.' << TUTORIAL_VERSION_MINOR << std::endl;
  foosay();
  return EXIT_SUCCESS;
}
