#include <stdlib.h>
#include <stdio.h>

void print_matrix(double ** mat, const int m, const int n){
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf(" %.4f", mat[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int m = 4;
  int n = 5;
  // mat points to an array of pointers to doubles (of length m)
  double **mat = malloc(m*sizeof(double *));
  // mat[0] points to the beginning of an array of doubles (of length m*n)
  mat[0] = malloc(m*n*sizeof(double));

  for (int i=1; i < m; i++){
    // let the values of mat point to the beginning of each line in the matrix
    mat[i] = &(mat[0][n*i]);
  }

// loop collapsing :) From lecture week 3. Must be contiguous memory.
  for (int i = 0; i < m*n; i++) {
      mat[0][i] = 1;
  }
  print_matrix(mat, m, n),

  free(*mat); free(mat);
  return 0;
}
