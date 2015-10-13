#include "castle.h" 

#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <string>

#include "hdf5.h"
#include "hdf5_hl.h"

#include "castle_config.h"
#include "driver.h"
#include "input_file.h"

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
  std::string infile, prefix;
  int optc;
  while ((optc = getopt_long(argc, argv, GETOPTS, long_opts, NULL)) != -1) {
    switch (optc) {
      case 'i':
        infile = std::string(optarg);
        break;
      case 'p':
        prefix = std::string(optarg);
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
  if (show_usage == 1 || optind < argc || infile.empty() || prefix.empty()) {
    print_usage();
    return EXIT_FAILURE;
  }

  InputFile input_file(infile);
  std::cout << "Dataset has " << input_file.get_rows() << " rows by " 
            << input_file.get_cols() << "cols" << std::endl;

  // READ FILE - Todo, replace with Infile
  size_t rows = input_file.get_rows();
  size_t cols = input_file.get_cols();
  double *data = new double[rows * cols];
  double *next = new double[rows * cols];
  input_file.populate_data(data);

  // Run the simulation!
  steady_clock::time_point t_start = steady_clock::now();
  Driver d(std::string("Hello, World!"));
  d.run();
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
