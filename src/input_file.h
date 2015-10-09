#ifndef CASTLE_INPUT_FILE_H
#define CASTLE_INPUT_FILE_H

#include <string>

#include "hdf5.h"

class InputFile {
  private: 
    std::string _filename;
    hid_t _file_id;
    hsize_t _dims[2];
    double _width;
    double _depth;
    double _nu;
    double _sigma;

  public:
    InputFile(std::string prefix_);
    ~InputFile();
    int get_rows() const;
    int get_cols() const;
    double get_width() const;
    double get_depth() const;
    double get_nu() const;
    double get_sigma() const;
    void populate_data(double *data) const;
};

#endif
