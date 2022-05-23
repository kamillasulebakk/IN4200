#include "stdlib.h"
#include "stdio.h"
#include "omp.h"

// int main(int argc, char const *argv[]) {
//   // main_1();
//   main_2();
//   return 0;
// }

void dense_mat_vec_1(int m, int n, double *x, double *A, double *y)
{
int i, j;

#pragma omp parallel for private(j);
for (i=0; i<m; i++){
  double tmp = 0.0;
  for (j=0; j<n; j++)
    tmp += A[i*n+j]*y[j];
  x[i] = tmp;
  }
}

int main_1version() {
  int m = 10; //atoi(argv[1]);
  int n = 5; //atoi(argv[2]);

  double *A = malloc(m*n*sizeof(double)); // m*n matrix
  double *y = malloc(n * sizeof(double)); // n*1 vector
  double *x = malloc(m * sizeof(double)); // m*1 vector

  // Assign some values
  #pragma omp parallel for private(j)
  for (size_t i = 0; i < m; i++) {
      for (size_t j = 0; j < n; j++) {
          A[i*n + j] = i + j;
      }
  }

  #pragma omp parallel for
  for (size_t j = 0; j < n; j++) {
      y[j] = j;
  }

  dense_mat_vec_1(m, n, x, A, y);

  free(A);
  free(y);
  free(x);

  return 0;
}


int main_2version() {
  int m = 10; //atoi(argv[1]);
  int n = 5; //atoi(argv[2]);

  double *A = malloc(m*n*sizeof(double)); // m*n matrix
  double *y = malloc(n * sizeof(double)); // n*1 vector
  double *x = malloc(m * sizeof(double)); // m*1 vector

  // Assign some values
  #pragma omp parallel for private(j)
  for (size_t i = 0; i < m; i++) {
      for (size_t j = 0; j < n; j++) {
          A[i*n + j] = i + j;
      }
  }

  #pragma omp parallel for
  for (size_t j = 0; j < n; j++) {
      y[j] = j;
  }

  #pragma omp parallel
  {
  int thread_id = omp_get_thread_num();
  int num_threads = omp_get_num_threads();

  int start_m = (thread_id*m)/num_threads;
  int stop_m = ((thread_id+1)*m)/num_threads;

  dense_mat_vec_2(stop_m-start_m, n, &x[start_m], &A[start_m*n], y);
  }

  free(A);
  free(y);
  free(x);

  return 0;
}

void dense_mat_vec_2(int m, int n, double *x, double *A, double *y)
{
int i, j;

#pragma omp parallel for private(j);
for (i=0; i<m; i++){
  double tmp = 0.0;
  for (j=0; j<n; j++)
    tmp += A[i*n+j]*y[j];
  x[i] = tmp;
  }
}

int main(int argc, char const *argv[]) {
  main_1version();
  main_2version();
  return 0;
}