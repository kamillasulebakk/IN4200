#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#include "methods.h"

void PageRank_iterations (
  int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores
){
  size_t i, idx;
  int counter = 0, num_dangling = 0;
  double tmp_diff = 0, max_diff = 1; //just some random value to begin with
  double one_over_N = 1.0 / (double) N;
  double *tmp, W;
  double *new_scores = malloc(N*sizeof(double));

  // find dangling webpages
  char *node_is_dangling = malloc(N*sizeof(char));
  #pragma omp parallel for
  for (i=0; i<N; i++)
    node_is_dangling[i] = 1;

  #pragma omp parallel for
  for (i=0; i<row_ptr[N]; i++)
    node_is_dangling[col_idx[i]] = 0;

  int *dangling_nodes = malloc(N*sizeof(int));
  // #pragma omp parallel for reduction(+:num_dangling)
  for (i=0; i<N; i++)
    if (node_is_dangling[i] == 1) {
      dangling_nodes[num_dangling] = i;
      num_dangling++;
    }

  free(node_is_dangling);
  dangling_nodes = realloc(dangling_nodes, num_dangling*sizeof(int));

  if (num_dangling > 0){
    printf("Number of dangling nodes %d\n", num_dangling);
    printvec_i(dangling_nodes, num_dangling);
  }

  #pragma omp parallel for
  for (i=0; i<N; i++)
    scores[i] = one_over_N;

  printf("Entering parallel region\n");
  #pragma omp parallel
  {
  while (epsilon <= max_diff){
    #pragma omp master
    {
    max_diff = 0;
    W = 0.0;
    }

    #pragma omp barrier

    #pragma omp for reduction(+:W)
    for (i=0; i<num_dangling; i++)
      W += scores[dangling_nodes[i]];

    // #pragma omp parallel for reduction(max:new_scores) private(i, idx, tmp_diff)
    #pragma omp for private(idx, tmp_diff) reduction(max: max_diff)
    for (i=0; i<N; i++) {
      new_scores[i] = 0.0;
      for (idx=row_ptr[i]; idx<row_ptr[i+1]; idx++)
        new_scores[i] += val[idx]*scores[col_idx[idx]];
      new_scores[i] *= d;
      new_scores[i] += (1 - d + d*W)*one_over_N;
      tmp_diff = fabs(new_scores[i] - scores[i]);
      if (tmp_diff > max_diff){
        max_diff = tmp_diff;
      }
    }

    #pragma omp barrier
    #pragma omp master
    {
    // swap pointers to scores and new_scores
    tmp = new_scores;
    new_scores = scores;
    scores = tmp;
    counter++;
    }
  } // end of while loop
  } // end of the entire parallel region


  printf("Number of iterations until convergence:\n");
  printf("%d\n", counter);

  // needed so that the right array are copied into final array with scores
  if (counter % 2 == 1) {
    tmp = new_scores;
    new_scores = scores;
    scores = tmp;
    for (i=0; i<N; i++)
      scores[i] = new_scores[i];
  }

  free(new_scores);
  free(dangling_nodes);
}
