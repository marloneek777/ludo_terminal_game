#include "random.h"
#include <chrono>
#include <random>
int Random::RandomInRange(int min_value, int hi_value) {
  static uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  static std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
  static std::mt19937 mgen(ss);

  if (min_value <= hi_value) {
    std::uniform_int_distribution<std::mt19937::result_type> mintohi(min_value, hi_value);
    return mintohi(mgen);
  }
  else {
    std::uniform_int_distribution<std::mt19937::result_type> mintohi(hi_value, min_value);
    return mintohi(mgen);
  }
}