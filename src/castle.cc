#include "castle.h" 

#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include <chrono>

#include "hdf5.h"
#include "hdf5_hl.h"

#include "mymath.h"
#include "castle_config.h"

#define GETOPTS "i:p:r:t:"
static char *progname;
static struct option long_opts[] = {
  {"infile", required_argument, NULL, 'i'},
  {"prefix", required_argument, NULL, 'p'},
  {"output-rate", required_argument, NULL, 'r'},
  {"timesteps", required_argument, NULL, 't'},
  {NULL, 0, NULL, 0}
};

int main(int argc, char *argv[]) {
  using namespace std::chrono;
  progname = argv[0];
  int show_usage = 0;
  int outrate = 1, timesteps = 17;
  char *infile = NULL, *prefix = NULL;
  int optc;
  while ((optc = getopt_long(argc, argv, GETOPTS, long_opts, NULL)) != -1) {
    switch (optc) {
      case 'i':
        if (infile != NULL) {
          free(infile);
        }
        infile = strdup(optarg);
        break;
      case 'p':
        if (prefix != NULL) {
          free(prefix);
        }
        prefix = strdup(optarg);
        break;
      case 'r':
        outrate = atoi(optarg);
        break;
      case 't':
        timesteps = atoi(optarg);
        if (timesteps < 1) {
          fprintf(stderr, "Invalid value for timesteps: %s, must be a number greater than 1.\n", optarg);
          show_usage = 1;
        }
        break;
      default:
          show_usage = 1;
    }
  }
  if (show_usage == 1 || optind < argc || infile == NULL || prefix == NULL) {
    print_usage();
    return EXIT_FAILURE;
  }
  // READ FILE
  hsize_t dims[2];
  hid_t file_id;
  if ((file_id = H5Fopen(infile, H5F_ACC_RDONLY, H5P_DEFAULT)) < 0) {
    print_usage();
    return EXIT_FAILURE;
  }
  if (H5LTget_dataset_info(file_id, CASTLE_DATASET, dims, NULL, NULL) < 0) {
    print_usage();
    return EXIT_FAILURE;
  }
  size_t rows = dims[0];
  size_t cols = dims[1];
  double *data = new double[rows * cols];
  double *next = new double[rows * cols];
  double width, depth, nu, sigma; 
  if (H5LTread_dataset_double(file_id, CASTLE_DATASET, data) < 0
   || H5LTget_attribute_double(file_id, "/domain/", "width", &width) < 0 
   || H5LTget_attribute_double(file_id, "/domain/", "depth", &depth) < 0 
   || H5LTget_attribute_double(file_id, "/properties/", "nu", &nu) < 0 
   || H5LTget_attribute_double(file_id, "/properties/", "sigma", &sigma) < 0) {
    fprintf(stderr, "Encountered an issue reading the dataset\n");
    return EXIT_FAILURE;
  };
  H5Fclose(file_id);

  // Run the simulation!
  steady_clock::time_point t_start = steady_clock::now();
  foosay();
  steady_clock::time_point t_end = steady_clock::now();
  // End the simulation!

  duration<double> runtime = duration_cast<duration<double>>(t_end - t_start);
  std::cout << "Runtime: " << runtime.count() << " seconds." << std::endl;
  delete[] data;
  delete[] next;
  return EXIT_SUCCESS;
} 


void print_usage(void) {
  fprintf(stderr, "%s: A simple 2D simulation of the diffusion equation.\n", progname);
  fprintf(stderr, "Usage: %s [OPTIONS]\n", progname);
  fprintf(stderr, "  -i,  --infile            Path to input file       [required]\n"
                  "  -p,  --prefix            Output filename prefix   [required]\n"
                  "  -r,  --output-rate       Timesteps between output [optional]\n"
                  "  -t,  --timesteps         Simulation Timesteps     [optional]\n");
}
