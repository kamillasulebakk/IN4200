#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char const *argv[]) {
  MPI_Init (&argc, &argv);

  int rank, size;

  int m = 10;

  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  my_MPI_rank = rank;

  if (my_MPI_rank == 0){
    other_MPI_rank = 1;
  }
  else{
    other_MPI_rank = 0;
  }

  int *my_sub_list = malloc(m*sizeof(int));
  for (int i=0; i<m; i++)
    my_sub_list[i] = i;

  compare_split(m, my_sub_list, my_MPI_rank, other_MPI_rank);

  MPI_Finalize();

  return 0;
}

void compare_split(int m, *my_sub_list, int my_MPI_rank, int other_MPI_rank){
  int rank;
  MPI_Status status;
  MPI_Request request;

  int *other_list = (m*sizeof(int));
  int *merge_list = (2*m*sizeof(int));

  MPI_Recv(other_list, m, MPI_INT, other_MPI_rank, 0, MPI_COMM_WORLD, &status);
  MPI_Send(my_sub_list, m, MPI_INT, my_MPI_rank, 0, MPI_COMM_WORLD);
  MPI_Wait(&request, &status);

  merge(m, *my_sub_list, *other_list, *merge_list);

  if (my_MPI_rank < other_MPI_rank){
    for (int i=0; i<m; i++)
      my_sub_list[i] = merge_list[i];
  }

  else{
    for (int i=m; i<2*m; i++)
      my_sub_list[i] = merge_list[i];

  free(other_list);
  free(merge_list);
  }


void merge(int m, int *sorted_list1, int *sorted_list2, int *merge_list) {
  int i = 0;
  int j = 0;
  int k = 0;

  while (i<m && j<m){
    if (sorted_list1[i] <= sorted_list2[j]){
      merge_list[k] = sorted_list1[i];
      i++;
    }

    else{
      merge_list[k] = sorted_list2[j];
      j++;
    }
    k++;
  }

  for (i; i<m; i++){
    merge_list[k] = sorted_list2[i];
    k++;
  }

  for (j; j<m; j++){
    merge_list[k] = sorted_list2[j];
    k++;
  }

  printvec_i(merge_list, 2*m);
}