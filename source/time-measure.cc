#include "time-measure.hpp"

using namespace std;

uint64_t rdtsc() {
  uint32_t lo, hi;
  __asm__ __volatile__ (
      "xorl %%eax, %%eax\n"
      "cpuid\n"
      "rdtsc\n"
      : "=a" (lo), "=d" (hi)
      :
      : "%ebx", "%ecx" );
  return (uint64_t)hi << 32 | lo;
}
