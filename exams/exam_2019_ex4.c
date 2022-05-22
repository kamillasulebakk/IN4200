#include "mpi.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char *argv[]) {
  int i, rank, size, own_value, in_value, out_value;

  MPI_Init (&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  MPI_Request request;
  MPI_Status status;

  const int receive_from = (rank+2)%size;
  const int send_to = (rank-2+size)%size;

  own_value = rank;
  out_value = rank;

  for (i=0; i<(size/2-1); i++){
    MPI_Irecv(&in_value, 1, MPI_INT, receive_from, 0, MPI_COMM_WORLD, &request);
    MPI_Send(&out_value, 1, MPI_INT, send_to, 0, MPI_COMM_WORLD);
    MPI_Wait(&request, &status);
    own_value += in_value;
    out_value = in_value;
  }
  printf("Rank %d: %d\n", rank, own_value);

  MPI_Finalize();

  return 0;
}
