#include <stdio.h>

extern long access_memory(long *array);

int main() {
  long array[8];
  long result = 0;
  for (int i = 0; i < 256; i++) {
    result += access_memory(array);
  }

  printf("result = %ld\n", result);
  return 0;
}
