#include <iostream>
#include <lib/lib.h>
#include <spdlog/spdlog.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    spdlog::error("Usage: {} <int> <int>", argv[0]);
    return 1;
  }
  int a = std::stoi(argv[1]);
  int b = std::stoi(argv[2]);

  spdlog::info("Sum of {} and {} is {}", a, b, sum(a, b));
  spdlog::info("Product of {} and {} is {}", a, b, mul(a, b));

  return 0;
}
