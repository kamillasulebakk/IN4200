#include <stdbool.h>
#include <stdio.h>
#include <math.h>
void compare_int(const int a, const int b)
{
  if (a == b)
    printf("Yay\n");
  else
    printf("Nay\n");
}

void compare_array_double(const double * const a, const double * const b, const int N)
{
  bool is_equal = true;
  const double tol = 1e-6;

  for (size_t i = 0; i < N; i++)
    if (abs(a[i] - b[i]) > tol)
      is_equal = false;

  if (is_equal)
    printf("Yay\n");
  else
    printf("Nay\n");
}

void print_array_i(const int * const a, const int N)
{
  for (size_t i = 0; i < N; i++)
    printf(" %d\n", a[i]);
  printf("\n");
}

void print_array_d(const double * const a, const int N)
{
  for (size_t i = 0; i < N; i++)
    printf(" %f\n", a[i]);
  printf("\n");
}
