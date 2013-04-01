#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#ifdef NDEBUG
#define PRINT_FUNCTION_NAME do {} while(0)
#else
#define PRINT_FUNCTION_NAME do {                \
    printf("%s\n", __func__);                   \
  } while(0)
#endif

static void bubble_sort(int *array, int length) {
  PRINT_FUNCTION_NAME;

  for (int i = (length - 1); i > 0; i--) {
    for (int j = 1; j <= i; j++) {
      if (array[j - 1] > array[j]) {
        int temp = array[j - 1];
        array[j - 1] = array[j];
        array[j] = temp;
      }
    }
  }
}

static void insertion_sort(int *array, int length) {
  PRINT_FUNCTION_NAME;

  for (int i = 1 ; i <= (length - 1); i++) {
    int index = i;
    int tmp;

    while (index > 0 && array[index] < array[index - 1]) {
      tmp = array[index];
      array[index] = array[index - 1];
      array[index - 1] = tmp;

      index--;
    }
  }
}

static int partition(int *array, int left, int right) {
  int pivot = array[left];
  int i = left, j = right + 1;

  while (1) {
    do {
      ++i;
    } while(array[i] <= pivot && i <= right);

    do {
      --j;
    } while(array[j] > pivot);

    if( i >= j ) break;
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;

  }

  int temp = array[left];
  array[left] = array[j];
  array[j] = temp;

  return j;
}

static void quick_sort_recursive(int *array, int left, int right) {
  if (left < right) {
    int j = partition(array, left, right);
    quick_sort_recursive(array, left, j - 1);
    quick_sort_recursive(array, j + 1, right);
  }
}

static void quick_sort(int *array, int length) {
  PRINT_FUNCTION_NAME;
  quick_sort_recursive(array, 0, length - 1);
}

static void merge(int *array, int *temp, int left, int mid, int right) {
  int left_end = mid - 1;
  int tmp_pos = left;
  int num_elements = right - left + 1;

  while ((left <= left_end) && (mid <= right)) {
    if (array[left] <= array[mid]) {
      temp[tmp_pos] = array[left];
      tmp_pos = tmp_pos + 1;
      left = left +1;
    } else {
      temp[tmp_pos] = array[mid];
      tmp_pos = tmp_pos + 1;
      mid = mid + 1;
    }
  }

  while (left <= left_end) {
    temp[tmp_pos] = array[left];
    left = left + 1;
    tmp_pos = tmp_pos + 1;
  }

  while (mid <= right) {
    temp[tmp_pos] = array[mid];
    mid = mid + 1;
    tmp_pos = tmp_pos + 1;
  }

  for (int i = 0; i <= num_elements; i++) {
    array[right] = temp[right];
    right = right - 1;
  }
}

static void merge_sort_recursive(int *array, int *temp, int left, int right) {
  if (right > left) {
    int mid = (right + left) / 2;
    merge_sort_recursive(array, temp, left, mid);
    merge_sort_recursive(array, temp, mid + 1, right);

    merge(array, temp, left, mid + 1, right);
  }
}

static void merge_sort(int *array, int length) {
  PRINT_FUNCTION_NAME;

  int *temporary = malloc(sizeof(int) * length);
  assert(temporary);

  merge_sort_recursive(array, temporary, 0, length - 1);

  free(temporary);
}

static void show_usage(const char *program_name) {
  printf("usage: %s [--bubble-sort | --insertion-sort | --quick-sort\n"
         "          |--merge-sort ]\n", program_name);
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

int main(int argc, char **argv) {
  if (argc != 2) {
    show_usage(argv[0]);
    return 1;
  }

  int array[] = { 74, 85, 28, 4, 49, 89, 27, 26, 70, 21,
                  30, 18, 69, 66, 18, 20, 93, 39, 72, 53,
                  5, 5, 7, 1024};
  int length = sizeof(array) / sizeof(array[0]);
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

  {
    uint64_t begin = rdtsc();
    sort_function(array, length);
    printf("time = %ld\n", (long) (rdtsc() - begin));
  }

  assert(is_sorted(array, length));

  return 0;
}
