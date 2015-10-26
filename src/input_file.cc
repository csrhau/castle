#include "input_file.h"

#include <string>
#include <exception>

#include "hdf5.h"
#include "hdf5_hl.h"

#include "castle_config.h"

InputFile::InputFile(std::string filename_) : _filename(filename_) {
  if ((_file_id = H5Fopen(_filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT)) < 0) {
    throw std::invalid_argument(std::string("Invalid filename: ") + filename_);
  }
  if (H5LTget_dataset_info(_file_id, CASTLE_DATASET, _dims, NULL, NULL) < 0) {
    throw std::logic_error("unable to read dataset info");
  } 
  if (H5LTget_attribute_double(_file_id, "/domain/", "width", &_width) < 0 
   || H5LTget_attribute_double(_file_id, "/domain/", "depth", &_depth) < 0 
   || H5LTget_attribute_double(_file_id, "/properties/", "nu", &_nu) < 0 
   || H5LTget_attribute_double(_file_id, "/properties/", "sigma", &_sigma) < 0) {
    throw std::logic_error("unable to read dataset attribute");
  }
}

InputFile::~InputFile() {
  H5Fclose(_file_id);
}

int InputFile::get_rows() const {
  return _dims[0];
}
  
int InputFile::get_cols() const {
  return _dims[1];
}

double InputFile::get_width() const {
  return _width;
}

double InputFile::get_depth() const {
  return _depth;
}

double InputFile::get_nu() const {
  return _nu;
}

double InputFile::get_sigma() const {
  return _sigma;
}

void InputFile::populate_data(double *data) const {
  if (H5LTread_dataset_double(_file_id, CASTLE_DATASET, data) < 0) {
    throw std::logic_error("unable to read dataset");
  }
}
