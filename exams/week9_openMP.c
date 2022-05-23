 #include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#include "common/utils.h"

double serial(double *a, double *b, const int N) {
  double s = 0.0;
  for (size_t i=0; i<N; i++) {
    a[i] = 10.0 + 2*i;
    b[i] = 20.0 + sin(0.1*i);
  }

  for (size_t i=0; i<N-1; i++) {
    s += a[i];
    a[i+1] = cos(b[i]);
  }
  return s;
}

double parallel(double *a, double *b, const int N) {
  double s;
  #pragma omp parallel
  {
  #pragma omp master
  printf("Running %d threads\n", omp_get_num_threads());

  #pragma omp for
  for (size_t i=0; i<N; i++) {
    a[i] = 10.0 + 2*i;
    b[i] = 20.0 + sin(0.1*i);
  }

  #pragma omp single
  s = a[0];
  
  #pragma omp for reduction(+:s)
  for (size_t i=0; i<N-1; i++) {
    a[i+1] = cos(b[i]);
    s += a[i+1];
  }
  }

  return s;
}

int main(int argc, char const *argv[]) {

  int i, N = 10;

  double *a_s = (double*)malloc (N*sizeof(double));
  double *b_s = (double*)malloc (N*sizeof(double));
  double *a_p = (double*)malloc (N*sizeof(double));
  double *b_p = (double*)malloc (N*sizeof(double));


  compare_int(serial(a_s, b_s, N), parallel(a_p, b_p, N));
  compare_array_double(a_s, a_p, N);
  compare_array_double(b_s, b_p, N);

  free(a_s); free(b_s);
  free(a_p); free(b_p);

  return 0;
}
