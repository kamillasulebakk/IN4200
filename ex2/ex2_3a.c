#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

typedef const int ci;

void alloc_3d(double **** array, const int nx, const int ny, const int nz){
  *array = malloc(nx*sizeof(double**));
  (*array)[0] = (double**) malloc(nx*ny*sizeof(double*));
  (*array)[0][0] = (double*) malloc(nx*ny*nz*sizeof(double));

  for (int i=1; i < nx; i++)
    (*array)[i] = &((*array)[0][ny*i]);

  for (int i=1; i < nx*ny; i++)
    (*array)[0][i] = &((*array)[0][0][nz*i]);
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

void fill_v_basic(double ***v, ci nx, ci ny, ci nz){
  int i, j, k;
  const double const_factor = M_PI / ((nx-1)*(ny-1)*(nz-1));
  for (i=0; i<ny*nz; i++)
    v[0][0][i] = 2.0;
  for (i=1; i<nx; i++)
    for (j=0; j<ny; j++)
      for (k=0; k<nz; k++)
        v[i][j][k] = 2.0 + sin(i*j*k*const_factor);
}

void fill_v_fancy(double ***v, ci nx, ci ny, ci nz){
  int i, j, k;
  double s, c, s_add, c_add, tmp;
  const double const_factor = M_PI / ((nx-1)*(ny-1)*(nz-1));
  for (i=0; i<ny*nz; i++)
    v[0][0][i] = 2.0;
  for (i=1; i<nx; i++)
    for (j=0; j<ny; j++){
      s = 0.0;
      c = 1.0;
      s_add = sin(i*j*const_factor);
      c_add = cos(i*j*const_factor);
      for (k=0; k<nz; k++){
        v[i][j][k] = 2.0 + s;
        tmp = s;
        s = s*c_add + c*s_add;
        c = c*c_add - tmp*s_add;
      }
    }
}

int main(int argc, char const *argv[]) {
  const int nx=100, ny=1000, nz=10000;
  int i,j,k;
  double ***v, ***u, ***v1;

  alloc_3d(&u, nx, ny, nz);
  for (i=0; i<nx*ny*nz; i++)
    u[0][0][i] = 0;

  alloc_3d(&v, nx, ny, nz);
  fill_v_basic(v, nx, ny, nz);
  // print_3d(v, nx, ny, nz);

  // alloc_3d(&v1, nx, ny, nz);
  // fill_v_fancy(v1, nx, ny, nz);
  // print_3d(v1, nx, ny, nz);

  // bool equal = true;
  // for (i=0; i<nx*ny*nz; i++)
  //   if (abs(v[0][0][i] - v1[0][0][i]) > 1e-8){
  //     equal = false;
  //     printf("%d  %f  %f \n", i, v[0][0][i], v1[0][0][i]);
  //   }
  //
  // if (equal)
  //   printf("Success!\n");
  // else
  //   printf("Nooo\n");

  free(u[0][0]); free(u[0]); free(u);
  free(v[0][0]); free(v[0]); free(v);
  // free(v1[0][0]); free(v1[0]); free(v1);
  return 0;
}
