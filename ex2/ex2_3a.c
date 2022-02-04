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

bool array_3D_is_equal(double ***u, double ***v, ci length){
  bool is_equal = true;
  for (int i=0; i<length; i++)
    if (abs(u[0][0][i] - v[0][0][i]) > 1e-8){
      is_equal = false;
      printf("%d  %f  %f \n", i, u[0][0][i], v[0][0][i]);
    }

  return is_equal;
}

int main(int argc, char const *argv[]) {
  const int nx=100, ny=100, nz=1000, num_iter=100;
  int i,j,k;
  double ***v, ***u, ***v1, ***tmp;

  alloc_3d(&u, nx, ny, nz);
  for (i=0; i<nx*ny*nz; i++)
    u[0][0][i] = 0;

  alloc_3d(&v, nx, ny, nz);
  fill_v_basic(v, nx, ny, nz);
  // print_3d(v, nx, ny, nz);

  // alloc_3d(&v1, nx, ny, nz);
  // fill_v_fancy(v1, nx, ny, nz);
  // print_3d(v1, nx, ny, nz);

  // const bool is_equal = array_3D_is_equal(v, v1, nx*ny*nz)
  // if (equal) printf("Success!\n");
  // else printf("Nooo\n");

  for (int iter=1; iter<=num_iter; iter++){
    for (i=1; i<nx-1; i++)
      for (j=1; j<ny-1; j++)
        for (k=1; k<nz-1; k++)
          // mean of all neighboors
          u[i][j][k] = v[i][j][k] + (v[i-1][j][k] + v[i][j-1][k] + v[i][j][k-1] - 6*v[i][j][k] + v[i+1][j][k] + v[i][j+1][k] + v[i][j][k+1])/6;
    // printf("Iteration %d\nu\n", iter);
    // print_3d(u, nx, ny, nz);
    // printf("v\n");
    // print_3d(v, nx, ny, nz);
    tmp = u;
    u = v;
    v = tmp;
  }



  free(u[0][0]); free(u[0]); free(u);
  free(v[0][0]); free(v[0]); free(v);
  // free(v1[0][0]); free(v1[0]); free(v1);
  return 0;
}
