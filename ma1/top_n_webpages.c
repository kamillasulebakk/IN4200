#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "methods.h"

void top_n_webpages (int N, double *scores, int n){
  int *indices = malloc(n*sizeof(int));
  int *max_indices;
  size_t i, j, k, max_idx;
  double max_score;

  #pragma omp parallel private(i, max_idx)
  {
  const int num_threads = omp_get_num_threads();

  #pragma omp master
  {
  max_indices = malloc(num_threads*sizeof(int));
  }
  // this loop can not be parallelized because iterations are dependent on each other
  for (i = 0; i < n; i++) {
    max_idx = i;

    #pragma omp for
    for (j = i + 1; j < N; j++)
      if (scores[j] > scores[max_idx])
        max_idx = j;

    // which thread has the max_idx for which scores[max_idx] is greatest?
    max_indices[omp_get_thread_num()] = max_idx;
    #pragma omp barrier
    #pragma omp master
    {
    max_idx = max_indices[0];
    for (j = 1; j < num_threads; j++)
        if (scores[max_indices[j]] > scores[max_idx])
          max_idx = max_indices[j];

    swap_d(&(scores[max_idx]), &(scores[i]));
    indices[i] = max_idx;
    }
  }
  } // end of the entire parallel region

  printf("\nIndices of top %d webpages: \n", n);
  printvec_i(indices, n);

  printf("\nScores in decreasing order: \n");
  printvec_d(scores, n);

  free(indices);
}





