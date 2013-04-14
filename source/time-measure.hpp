#ifndef __TIME_MEASURE_HPP
#define __TIME_MEASURE_HPP

#include <cstdio>
#include <stdint.h>

uint64_t rdtsc();

#ifdef MEASURE_TIME

class TimeMeasure {
 public:
  TimeMeasure() {
    ticks_begin_ = rdtsc();
  }

  ~TimeMeasure() {
    uint64_t current_ticks = rdtsc();
    std::fprintf(stderr, "Ticks: %ld\n", current_ticks - ticks_begin_);
  }

 private:
  uint64_t ticks_begin_;
};

#else

class TimeMeasure { };

#endif // MEASURE_TIME

#endif // __TIME_MEASURE_HPP
