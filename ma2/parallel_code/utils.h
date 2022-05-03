#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

bool overlap_above(const int rank);
bool overlap_below(const int rank, const int num_procs);
int calculate_my_m(const int rank, const int num_procs, const int m);
void calculate_counts_and_displacement(
  int **send_counts, int **Sdispls, const int num_procs, const int m, const int n
);
void edit_counts_and_displs_from_scatter_to_gather(
  int *send_counts, int *displs, const int num_procs, const int n
);
#endif
