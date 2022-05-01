#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

int calculate_my_m(const int rank, const int num_procs, const int m);
bool overlap_above(const int rank);
bool overlap_below(const int rank, const int num_procs);
void calculate_counts_and_displacement(
  int **send_counts, int **Sdispls, const int num_procs, const int m, const int n
);
#endif
