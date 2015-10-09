#ifndef CASTLE_WRITER_H
#define CASTLE_WRITER_H
  
#include <string>

class Writer {
  private:
    std::string _prefix;

  public:
    Writer(std::string prefix_);
    ~Writer();
    void write();
};

#endif
