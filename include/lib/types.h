#pragma once

#include <string>
#include <vector>

// TODO: make this an abstract type
enum Diagnosis { M, B };

// This verbose representation of the datapoint in required by reflectcpp to
// parse the csv file
struct DataCSV {
  int id;

  // rfl::Rename<"diagnosis", Diagnosis> diagnosis;
  std::string label;

  double feature_1, feature_2;

  std::vector<double> to_features_array() const {
    return {feature_1, feature_2};
  }
  std::string get_label() const { return label; }
};
