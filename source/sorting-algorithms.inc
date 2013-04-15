#ifndef __SORTING_ALGORITHMS__INC
#define __SORTING_ALGORITHMS__INC

#include <algorithm>
#include <cassert>

#include "time-measure.hpp"

#define MAYBE_UNUSED __attribute__((unused))

static void MAYBE_UNUSED bubble_sort(int *array, int length) {
  for (int i = length; i > 0; i--) {
    for (int j = 1; j < i; j++) {
      if (array[j - 1] > array[j]) std::swap(array[j - 1], array[j]);
    }
  }
}

static void MAYBE_UNUSED insertion_sort(int *array, int length) {
  for (int i = 1; i < length; i++) {
    int index = i;

    while (index > 0 && array[index] < array[index - 1]) {
      std::swap(array[index], array[index - 1]);
      index--;
    }
  }
}

static int partition(int *array, const int length) {
  /* lifted from http://en.wikipedia.org/wiki/Quicksort */
  const int pivot_value = *array;
  std::swap(*array, array[length - 1]);
  int store_index = 0;

  for (int i = 0; i < (length - 1); i++) {
    if (array[i] <= pivot_value) {
      std::swap(array[i], array[store_index]);
      store_index++;
    }
  }
  std::swap(array[store_index], array[length - 1]);
  return store_index;
}

static void quick_sort_recursive(int *array, const int length) {
  if (length > 1) {
    const int pivot_index = partition(array, length);
    quick_sort_recursive(array, pivot_index);
    quick_sort_recursive(array + pivot_index + 1, length - pivot_index - 1);
  }
}

static void MAYBE_UNUSED quick_sort(int *array, int length) {
  quick_sort_recursive(array, length);
}

static void merge(int *array, int *buffer, int midpoint, int length) {
  int begin_a = 0, begin_b = midpoint;
  int *original_buffer = buffer;

  while (begin_a < midpoint && begin_b < length) {
    *buffer++ =
        array[begin_a] < array[begin_b] ? array[begin_a++] : array[begin_b++];
  }

  while (begin_a < midpoint) *buffer++ = array[begin_a++];
  while (begin_b < length) *buffer++ = array[begin_b++];

  std::copy(original_buffer, original_buffer + length, array);
}

static void merge_sort_recursive(int *array, int *buffer, const int length) {
  if (length > 1) {
    const int midpoint = length / 2;
    merge_sort_recursive(array, buffer, midpoint);
    merge_sort_recursive(array + midpoint, buffer + midpoint,
                         length - midpoint);

    merge(array, buffer, midpoint, length);
  }
}

static void MAYBE_UNUSED merge_sort(int *array, int length) {
  int *temporary = new int[length];
  merge_sort_recursive(array, temporary, length);
  delete[] temporary;
}

#ifndef NDEBUG
static int is_sorted(int *array, int length) {
  if (length == 0) return 1;

  for (int i = 1; i < length; i++) {
    if (array[i - 1] > array[i]) return 0;
  }

  return 1;
}
#endif /* NDEBUG */

static void sort_using(void (*sort_fn) (int *, int)) {
  int array_values[] = {
#include "numbers.inc"
  };
  int length = sizeof(array_values) / sizeof(array_values[0]);

#ifdef USE_MALLOC
  int *array = new int[length];
  for (int i = 0; i < length; i++) {
    array[i] = array_values[i];
  }
#else  /* USE_MALLOC */
  int *array = array_values;
#endif /* USE_MALLOC */

  sort_fn(array, length);
  assert(is_sorted(array, length) && "sorting is broken!");

#ifdef USE_MALLOC
  delete [] array;
#endif
}

#define GENERATE_BODY(sort_type)                \
  int main() {                                  \
    TimeMeasure measure_time;                   \
    (void) measure_time;                        \
    sort_using(sort_type ## _sort);             \
    return 0;                                   \
  }

#endif // __SORTING_ALGORITHMS__INC
