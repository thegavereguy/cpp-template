#pragma once

#include "lib/model.h"
#include "lib/types.h"
#include <rfl.hpp>
#include <rfl/csv.hpp>
#include <string>
#include <vector>

// Opens the csv and returns the data in some sort of data structure that can be
// used from training.
namespace tools {

template <typename T = double>
model::DataSet<T> load_csv(const std::string _filename) {
  const rfl::Result<std::vector<DataCSV>> result =
      rfl::csv::load<std::vector<DataCSV>>(_filename);

  model::DataSet<T> d;

  for (DataCSV f : result.value()) {
    model::DataPoint<double> t =
        model::DataPoint<double>(f.get_label(), f.to_features_array());

    d.add_datapoint(t);
  }
  return d;
};

} // namespace tools
