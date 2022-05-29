#include <stdio.h>
#include <stdlib.h>

void fill_2d(double ** mat, const int m, const int n, const double val){
  // loop collapsing (from lecture week 3). Must be contiguous memory.
  for (int i = 0; i < m*n; i++)
    mat[0][i] = val;
}

void zeros_2d(double *** mat, const int m, const int n){
  *mat = malloc(m*sizeof(double *)); // the star stands for VALUE OF MAT
  // mat[0] points to the beginning of an array of doubles (of length m*n)
  (*mat)[0] = malloc(m*n*sizeof(double));

  for (int i=1; i < m; i++){
    // let the values of mat point to the beginning of each line in the matrix
    (*mat)[i] = &((*mat)[0][n*i]);
  }
  fill_2d(*mat, m, n, 1.0);
}

int main(int argc, char const *argv[]) {
  int n;
  int m;
  int p;

  double **A, **B, **C;

  zeros_2d(&A, n, m);
  zeros_2d(&B, m, p);
  zeros_2d(&C, n, p);

  // for (int i=0; i<n; i++){
  //   for (int j=0; j<p; j++){
  //     for (int k=0; k<m; k++)
  //       C[i][j] = A[i][k]*B[k][j];
  //   }
  // }
  int i, j, k;

  for (i=0; i<n; i++){
    for (j=0; j<p%4; j++){
      for (k=0; k<m; k++)
        C[i][j] = A[i][k]*B[k][j];
    }


    for (j; j<p; j+=4){
      for (int k=0; k<m; k++){
        C[i][j] = A[i][k]*B[k][j+1];
        C[i][j+1] = A[i][k]*B[k][j+2];
        C[i][j+2] = A[i][k]*B[k][j+3];
        C[i][j+3] = A[i][k]*B[k][j+4];
      }
    }
  }


  return 0;
}
