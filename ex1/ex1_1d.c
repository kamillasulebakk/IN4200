#include <stdlib.h>
#include <stdio.h>

void fill_3d(double **** array, const int nx, const int ny, const int nz, const double val){
  *array = malloc(nx*sizeof(double**));
  (*array)[0] = (double**) malloc(nx*ny*sizeof(double*));
  (*array)[0][0] = (double*) malloc(nx*ny*nz*sizeof(double));

  for (int i=1; i < nx; i++)
    (*array)[i] = &((*array)[0][ny*i]);

  for (int i=1; i < nx*ny; i++)
    (*array)[0][i] = &((*array)[0][0][nz*i]);

  for (int i=0; i<nx*ny*nz; i++)
    (*array)[0][0][i] = val;
}

void print_3d(double ***A, const int nx, const int ny, const int nz) {
  for (int i=0; i<nx; i++){
    for (int j=0; j<ny; j++){
      for (int k=0; k<nz; k++)
        printf(" %f", A[i][j][k]);
      printf("\n");
    }
    printf("\n\n");
  }
}

int main(int argc, char const *argv[]) {
  int nx=2, ny=3, nz=4;
  int i,j,k;
  double *** array;
  fill_3d(&array, nx, ny, nz, 1.0);
  print_3d(array, nx, ny, nz);

  for (int i=0; i<ny; i++)
    array[0][i][1] = 0.0;
  print_3d(array, nx, ny, nz);


  free(array[0][0]); free(array[0]); free(array);
  return 0;
}
