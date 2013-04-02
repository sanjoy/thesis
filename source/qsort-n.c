#include <stdio.h>
#include <stdlib.h>

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
  quick_sort_recursive(array, 0, length - 1);
}

int main(int argc, char **argv) {
  int array[] = {
#include "numbers.inc"
  };
  if (argc != 2) {
    printf("usage: %s [element-count]\n", argv[0]);
    return 1;
  }

  int length = atoi(argv[1]);
  quick_sort(array, length);
}
