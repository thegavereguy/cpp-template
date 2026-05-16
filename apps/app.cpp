#include "lib/tools.h"

#include <spdlog/spdlog.h>

#include <exception>
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 4) {
    spdlog::error("Usage: {} <traning_set> <validation_set> <testing_set>",
                  argv[0]);
    return 1;
  }
  const std::string _training_filepath(argv[1]);
  const std::string _validation_filepath(argv[2]);
  const std::string _testing_filepath(argv[3]);

  model::DataSet<double> training_set;
  model::DataSet<double> validation_set;
  model::DataSet<double> testing_set;
  try {
    training_set = tools::load_csv<double>(_training_filepath);
    validation_set = tools::load_csv<double>(_validation_filepath);
    testing_set = tools::load_csv<double>(_testing_filepath);

  } catch (std::exception &e) {
    spdlog::error("Error loading the files: {}", e.what());
    spdlog::info("Exiting");
    return 2;
  };

  spdlog::info("Training set loaded: {} samples",
               training_set.get_datapoints().size());
  spdlog::info("Validation set loaded: {} samples",
               validation_set.get_datapoints().size());
  spdlog::info("Testing set loaded: {} samples",
               testing_set.get_datapoints().size());

  return 0;
}
