#include <stdlib.h>

#include "utils.h"

int calculate_my_m(const int rank, const int num_procs, const int m)
{
  const int my_start = rank*m/num_procs - overlap_above(rank);
  const int my_stop = (rank+1)*m/num_procs + overlap_below(rank, num_procs);
  const int my_m = my_stop - my_start;
  return my_m;
}

bool overlap_above(const int rank)
{
  return (rank != 0);
}

bool overlap_below(const int rank, const int num_procs)
{
  return (rank != (num_procs - 1));
}

void calculate_counts_and_displacement(
  int **send_counts, int **Sdispls, const int num_procs, const int m, const int n
) {
  *send_counts = malloc(num_procs*sizeof(int));
  *Sdispls = malloc(num_procs*sizeof(int));
  for (int rank = 0; rank < num_procs; rank++){
    (*send_counts)[rank] = calculate_my_m(rank, num_procs, m)*n;
  }

  (*Sdispls)[0] = 0;
  for (size_t rank = 1; rank < num_procs; rank++){
    (*Sdispls)[rank] = (*Sdispls)[rank-1] + (*send_counts)[rank-1];
    if (overlap_above(rank))
      (*Sdispls)[rank] -= n;
    if (overlap_below(rank-1, num_procs))
      (*Sdispls)[rank] -= n;
  }
}
