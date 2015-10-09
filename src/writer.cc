#include "writer.h"

#include <string>
#include <iostream>

Writer::Writer(std::string prefix_) : _prefix(prefix_) {

}

Writer::~Writer() {

}

void Writer::write() {
  std::cout << " Ran " << std::endl;
}
