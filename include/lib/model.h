#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <limits>
#include <map>
#include <spdlog/spdlog.h>
#include <string>
#include <utility>
#include <vector>

namespace model {

template <typename T> class DataPoint {
private:
  std::vector<T> features;
  std::string label;

public:
  DataPoint(std::string l, std::vector<T> v) : label(l), features(v) {}
  DataPoint(std::vector<T> v) : label("unlabeled"), features(v) {}

  std::string get_label() const { return this->label; }
  std::vector<T> get_features() const {
    return features;
  } // const method, doesn't allow to change the object it's called on.
  std::vector<T> &get_mut_features() {
    return features;
  } // non-const method, allows to change the object it's called on.

  void apply_norm(
      const std::pair<const std::vector<T>, const std::vector<T>> norm_params) {
    const std::vector<T> min_values = norm_params.first;
    const std::vector<T> max_values = norm_params.second;

    for (size_t i = 0; i < features.size(); i++) {
      T range = max_values[i] - min_values[i];
      if (range != 0) {
        features[i] = (features[i] - min_values[i]) / range;
      }
    }
  }
};

template <typename T> class DataSet {
private:
  std::vector<DataPoint<T>> datapoints;
  // TODO: ripensare sta roba
  std::vector<double> feature_means;
  std::vector<double> feature_stds;

  std::pair<std::vector<T>, std::vector<T>> normalization_params;

public:
  // TODO: implement normalization/standardization
  DataSet(std::vector<DataPoint<T>> d) : datapoints(d) {}
  DataSet() : datapoints() {}
  ~DataSet() { datapoints.clear(); }

  std::vector<DataPoint<T>> get_datapoints() const { return datapoints; }
  std::vector<DataPoint<T>> &get_mut_datapoints() { return datapoints; }
  void add_datapoint(DataPoint<T> d) { datapoints.push_back(d); }
  std::pair<std::vector<T>, std::vector<T>> get_normalization_params() const {
    return normalization_params;
  }

  void normalize() {
    spdlog::info("Normalizing dataset with {} datapoints", datapoints.size());

    if (this->get_datapoints().empty())
      return;

    size_t num_features = this->get_datapoints()[0].get_features().size();
    size_t num_points = this->get_datapoints().size();

    std::vector<T> min_values(num_features, std::numeric_limits<T>::max());
    std::vector<T> max_values(num_features, std::numeric_limits<T>::lowest());

    for (const DataPoint<T> &point : this->get_datapoints()) {
      for (size_t i = 0; i < num_features; i++) {
        if (point.get_features()[i] < min_values[i])
          min_values[i] = point.get_features()[i];
        if (point.get_features()[i] > max_values[i])
          max_values[i] = point.get_features()[i];
      }
    }
    this->normalization_params = {min_values, max_values};

    for (DataPoint<T> &point : this->get_mut_datapoints()) {
      for (size_t i = 0; i < num_features; i++) {
        T range = max_values[i] - min_values[i];
        if (range != 0) {
          point.get_mut_features()[i] =
              (point.get_features()[i] - min_values[i]) / range;
        }
      }
    }
  }
};

template <typename T>
T calculate_euclid_distance(const DataPoint<T> &a, const DataPoint<T> &b) {
  std::vector<T> feat_a = a.get_features();
  std::vector<T> feat_b = b.get_features();

  T sum = 0;

  for (size_t i = 0; i < feat_a.size(); ++i) {
    T diff = feat_a[i] - feat_b[i];
    sum += diff * diff;
  }
  return std::sqrt(sum);
}

// TODO: move this somewhere else
class Result {
private:
  std::string result_label;
  unsigned int k_value;
  double accuracy;

public:
  Result(std::string &label) : result_label(label) {};
  Result(std::string &label, unsigned int k, double a)
      : result_label(label), k_value(k), accuracy(a) {};
  void set_result_label(std::string &label) { this->result_label = label; }
  std::string get_result_label() { return this->result_label; }
  void set_k(unsigned int k) { this->k_value = k; }
  unsigned int get_k() { return this->k_value; }
  void set_accuracy(double a) { this->accuracy = a; }
  unsigned int get_accuracy() { return this->accuracy; }
};

enum Op_Type { Validate, Test };

}; // namespace model
