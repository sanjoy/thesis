#include <cstdio>

#include "time-measure.hpp"

using namespace std;

int numbers[] = {
#include "numbers.inc"
};

static int is_prime(int number) {
  for (int i = 2; i < (number / 2 + 1); i++) {
    if (number % i == 0) return 0;
  }
  return 1;
}

static double prime_mean(int *array, int size) {
  double total = 0.0;
  int count = 0;

  for (int i = 0; i < size; i++) {
    if (is_prime(numbers[i])) {
      count++;
      total += numbers[i];
    }
  }

  if (count == 0) return 0.0;
  return total / count;
}

int main(void) {
  printf("%lf\n", prime_mean(numbers, sizeof(numbers) / sizeof(numbers[0])));
  return 0;
}

TimeMeasure __measure_time;
