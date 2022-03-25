#include <stdlib.h>
#include <stdio.h>

#include "methods.h"

void top_n_webpages (int N, double *scores, int n){
  int *indices = malloc(N*sizeof(int));
  size_t i, j, max_idx;

  for (i=0; i<N; i++)
    indices[i] = i+1;

  // One by one move boundary of unsorted subarray
  for (i = 0; i < N - 1; i++) {
    // Find the minimum element in unsorted array
    max_idx = i;
    for (j = i + 1; j < N; j++)
      if (scores[j] > scores[max_idx])
        max_idx = j;

    // Swap the found minimum element
    // with the first element
    swap_d(&(scores[max_idx]), &(scores[i]));
    swap_i(&(indices[max_idx]), &(indices[i]));
  }

  printf("\nTop %d webpages: \n", n);
  printvec_i(indices, n);

  printf("\nScores in decreasing order: \n");
  printvec_d(scores, n);

  free(indices);
}





