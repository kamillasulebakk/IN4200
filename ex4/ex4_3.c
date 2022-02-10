#include <stdlib.h>
#include <stdio.h>

void print_matrix(double ** mat, const int m, const int n){
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf(" %.4f", mat[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void make_2D_array(double ***mat, int m, int n, double value){
  *mat = malloc(m*sizeof(double *));
  (*mat)[0] = malloc(m*n*sizeof(double));

  for (int i=1; i < m; i++){
    // let the values of mat point to the beginning of each line in the matrix
    (*mat)[i] = &((*mat)[0][n*i]);
  }
// loop collapsing :) From lecture week 3. Must be contiguous memory.
  for (int i = 0; i < m*n; i++) {
      (*mat)[0][i] = value;
  }
}

void matrix_multiplication(double **A, double **B, double ***C, int m, int n, int p){
  *C = malloc(n*sizeof(double *));
  (*C)[0] = malloc(n*p*sizeof(double));

  for (int i=1; i < n; i++){
    // let the values of mat point to the beginning of each line in the matrix
    (*C)[i] = &((*C)[0][p*i]);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < p; j++) {
      for (int k = 0; k < m; k++){
        (*C)[i][j] += A[i][k]*B[k][j];
      }
    }
  }
}
// Number of cache line loads (and) stores from (to) main memory:
// N = n*p*m
// C: N^3, A: N^3, B: N^3

// Assumes zero initialized C.
void matrix_multiplication_fast(double **A, double **B, double ***C, int m, int n, int p){
  *C = malloc(n*sizeof(double *));
  (*C)[0] = malloc(n*p*sizeof(double));

  for (int i=1; i < n; i++){
    // let the values of mat point to the beginning of each line in the matrix
    (*C)[i] = &((*C)[0][p*i]);
  }

  int rest = p%4;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < p-rest; j+=4) { // Stride by 4.
      for (int k = 0; k < m; k++) { // Inner dim in A and B.
        (*C)[i][j]   += A[i][k]*B[k][j];
        (*C)[i][j+1] += A[i][k]*B[k][j+1];
        (*C)[i][j+2] += A[i][k]*B[k][j+2];
        (*C)[i][j+3] += A[i][k]*B[k][j+3];
      }
    // Rest loop.
    for (int j = p-rest; j < p; j++){
      for (int k = 0; k < m; k++){
        (*C)[i][j] += A[i][k]*B[k][j];
      }
    }
    }
  }
}
// Number of cache line loads (and) stores from (to) main memory:
// N = i*p-rest*k

int main() {
  int m = 5;
  int n = 4;
  int p = 10;
  double **A, **B, **C;

  make_2D_array(&A, n, m, 1.0);
  make_2D_array(&B, m, p, 2.0);

  print_matrix(A, n, m);
  print_matrix(B, m, n);

  // matrix_multiplication(A, B, &C, m, n, p);
  // print_matrix(C, n, p);

  matrix_multiplication_fast(A, B, &C, m, n, p);
  print_matrix(C, n, p);

  free(*A); free(A);
  free(*B); free(B);
  free(*C); free(C);
  return 0;
}