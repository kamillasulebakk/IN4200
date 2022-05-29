#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include "stdbool.h"

void calculate_displacement(cint num_procs, int my_length, int **displs, int **sendcounts)
{
  *displs = malloc(num_procs*sizeof(int));
  (*displs)[0] = 0;
  for (size_t i = 0; i < num_procs; i++)
    (*sendcounts)[i] = my_length;
  for (size_t i = 1; i < num_procs; i++){
    (*displs)[i] = (*displs)[i-1] + my_length;
  }
}

void para_matvec (int n, double **A, double *x, double *y){
  int rank, size;

  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  const bool i_am_root = (rank == 0);

  double *my_y;
  if (i_am_root)
    y = y;

  else
    my_y = y;

  MPI_Bcast (x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  double my_A = A;
  int my_length = n/size;
  int i, j;

  for (i = 0; i < my_length; i++){
    for (j = 0; j < n; j++)
      my_y[i] += my_A[i][j]*x[j];
  }

  int *displs;
  int *sendcounts;

  calculate_displacement(num_procs, my_length, &displs, &sendcounts);
  MPI_Gatherv(my_y, my_length, displs, MPI_DOUBLE, y, sendcounts, MPI_DOUBLE, 0, MPI_COMM_WORLD);

}


int main(int argc, char const *argv[]) {
  MPI_Init (&argc, &argv);

  int rank, size;

  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  para_matvec();


  return 0;
}