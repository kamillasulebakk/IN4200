#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "methods.h"

void PageRank_iterations (
  int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores
){
  size_t i, idx;
  int counter = 0, num_dangling = 0;
  double tmp_diff = 0, diff = 1; //just some random value to begin with
  double one_over_N = 1.0 / (double) N;
  double *tmp, W;
  double *new_scores = malloc(N*sizeof(double));

  // find dangling webpages
  char *node_is_dangling = malloc(N*sizeof(char));
  for (i=0; i<N; i++)
    node_is_dangling[i] = 1;

  for (i=0; i<row_ptr[N]; i++)
    node_is_dangling[col_idx[i]] = 0;

  int *dangling_nodes = malloc(N*sizeof(int));
  for (i=0; i<N; i++)
    if (node_is_dangling[i] == 1) {
      dangling_nodes[num_dangling] = i;
      num_dangling++;
    }

  free(node_is_dangling);
  dangling_nodes = realloc(dangling_nodes, num_dangling*sizeof(int));

  printf("Number of dangling nodes %d\n", num_dangling);
  printvec_i(dangling_nodes, num_dangling);

  for (i=0; i<N; i++)
    scores[i] = one_over_N;

  // printvec_d(scores, N);

  while (epsilon <= diff){
    // #pragma omp parallel shared(epsilon,diff)
    diff = 0;
    // Can this go outside loop ?
    W = 0.0;
    for (i=0; i<num_dangling; i++)
      W += scores[dangling_nodes[i]];

    for (i=0; i<N; i++) {
      new_scores[i] = 0.0;
      for (idx=row_ptr[i]; idx<row_ptr[i+1]; idx++)
        new_scores[i] += val[idx]*scores[col_idx[idx]];
      new_scores[i] *= d;
      new_scores[i] += (1 - d + d*W)*one_over_N;
      tmp_diff = fabs(new_scores[i] - scores[i]);
      if (tmp_diff > diff){
        // #pragma omp critical
        diff = tmp_diff;
      }
    }

    // swap pointers to scores and new_scores
    tmp = new_scores;
    new_scores = scores; // new_scores is set back to 1/N
    scores = tmp; // scores will be the previous scores calculated
    // printvec_d(scores, N);
    counter++;
  }

  printf("Number of iterations until convergence:\n");
  printf("%d\n", counter);

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
