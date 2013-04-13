#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#ifdef NDEBUG
#define PRINT_FUNCTION_NAME do {} while(0)
#else
#define PRINT_FUNCTION_NAME printf("%s\n", __func__)
#endif /* NDEBUG */

#define swap(a, b) do {                         \
    int temp = (a); (a) = (b); (b) = temp;      \
  } while(0)

static void bubble_sort(int *array, int length) {
  PRINT_FUNCTION_NAME;

  for (int i = length; i > 0; i--) {
    for (int j = 1; j < i; j++) {
      if (array[j - 1] > array[j]) swap(array[j - 1], array[j]);
    }
  }
}

static void insertion_sort(int *array, int length) {
  PRINT_FUNCTION_NAME;

  for (int i = 1; i < length; i++) {
    int index = i;

    while (index > 0 && array[index] < array[index - 1]) {
      swap(array[index], array[index - 1]);
      index--;
    }
  }
}

static int partition(int *array, const int length) {
  /* lifted from http://en.wikipedia.org/wiki/Quicksort */
  const int pivot_value = *array;
  swap(*array, array[length - 1]);
  int store_index = 0;

  for (int i = 0; i < (length - 1); i++) {
    if (array[i] <= pivot_value) {
      swap(array[i], array[store_index]);
      store_index++;
    }
  }
  swap(array[store_index], array[length - 1]);
  return store_index;
}

static void quick_sort_recursive(int *array, const int length) {
  if (length > 1) {
    const int pivot_index = partition(array, length);
    quick_sort_recursive(array, pivot_index);
    quick_sort_recursive(array + pivot_index + 1, length - pivot_index - 1);
  }
}

static void quick_sort(int *array, int length) {
  PRINT_FUNCTION_NAME;
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

  memcpy(array, original_buffer, sizeof(int) * length);
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

static void merge_sort(int *array, int length) {
  PRINT_FUNCTION_NAME;

  int *temporary = malloc(sizeof(int) * length);
  assert(temporary && "malloc failed");

  merge_sort_recursive(array, temporary, length);

  free(temporary);
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

#ifdef PRINT_TIME
inline uint64_t __attribute__((always_inline)) rdtsc(void) {
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
#endif /* PRINT_TIME */

static void show_usage(const char *program_name) {
  printf("usage: %s [--bubble-sort | --insertion-sort | --quick-sort\n"
         "          |--merge-sort ]\n", program_name);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    show_usage(argv[0]);
    return 1;
  }

  int array_values[] = {
#include "numbers.inc"
  };
  int length = sizeof(array_values) / sizeof(array_values[0]);

#ifdef USE_MALLOC
  int *array = malloc(sizeof(int) * length);
  for (int i = 0; i < length; i++) {
    array[i] = array_values[i];
  }
#else  /* USE_MALLOC */
  int *array = array_values;
#endif /* USE_MALLOC */

  void (*sort_function) (int *, int);

  if (strcmp(argv[1], "--bubble-sort") == 0) {
    sort_function = bubble_sort;
  } else if (strcmp(argv[1], "--insertion-sort") == 0) {
    sort_function = insertion_sort;
  } else if (strcmp(argv[1], "--quick-sort") == 0) {
    sort_function = quick_sort;
  } else if (strcmp(argv[1], "--merge-sort") == 0) {
    sort_function = merge_sort;
  } else {
    show_usage(argv[0]);
    return 1;
  }

#ifdef PRINT_TIME
  {
    uint64_t begin = rdtsc();
#endif

    sort_function(array, length);

#ifdef PRINT_TIME
    printf("time = %ld\n", (long) (rdtsc() - begin));
  }
#endif

  assert(is_sorted(array, length) && "array not sorted");
  return 0;
}
