#include "stdlib.h"
#include "stdio.h"
#include "omp.h"

void fill_2d(double ** mat, const int m, const int n, const double val){
  for (int i = 0; i < m*n; i++)
    mat[0][i] = val;
}

void zeros_2d(double *** mat, const int m, const int n){
  *mat = malloc(m*sizeof(double *));
  (*mat)[0] = malloc(m*n*sizeof(double));

  for (int i=1; i < m; i++){
    (*mat)[i] = &((*mat)[0][n*i]);
  }
  fill_2d(*mat, m, n, 0.0);
}

int main(int argc, char const *argv[]) {
  int m = 10; //atoi(argv[1]);
  int n = 5; //atoi(argv[2]);

  double **mat;
  double *x;
  double *y = malloc(n*sizeof(double));
  for (i=0; i<n; i++){
    y[i] = i;
  }

  zeros_2d(&mat, m, n);
  fill_2d(mat, m, n, 1);

  return 0;
}

void dense_mat_vec(int m, int n, double *x, double *A, double *y){
  int i, j;
  for (i=0; i<m; i++){
    double tmp=0;
    for (j=0; j<n; j++)
      temp += A[i*n+j]*y[j];
    x[i] = tmp;
  }
}