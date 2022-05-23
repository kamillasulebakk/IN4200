#include <stdlib.h>
#include <stdio.h>

#include "common/utils.h"

int main(int argc, char const *argv[]) {
  const int N = 10;

  int a[N], b[N];

  for (size_t i = 0; i < N; i++) {
    a[i] = i;
    b[i] = -i;
  }

  printf("Address of a: %lu\n", &a);
  printf("Address of b: %lu\n", &b);
  // print_array_int(&a, N);
  // print_array_int(&b, N);

  int *tmp = &a;
  &a = &b;
  &b = tmp;

  printf("Address of a: %lu\n", &a);
  printf("Address of b: %lu\n", &b);
  // print_array_int(&a, N);
  // print_array_int(&b, N);

  return 0;
}