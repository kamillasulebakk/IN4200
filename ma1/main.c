#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

void read_graph_from_file (char *filename, int *N, int **row_ptr, int **col_idx, double **val);
void PageRank_iterations (int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores);
void top_n_webpages (int N, double *scores, int n);

int main(int argc, char const *argv[]) {
  double time_spent = 0.0;
  double start, stop;

  int N=0, *row_ptr, *col_idx;
  double *val;
  double d=1.00, epsilon=1e-7;
  // double d=0.85, epsilon=1e-6;
  int n = 3;

  // read_graph_from_file("simple-webgraph.txt", &N, &row_ptr, &col_idx, &val);
  // read_graph_from_file("simple-webgraph-invalid.txt", &N, &row_ptr, &col_idx, &val);
  // read_graph_from_file("100-webgraph.txt", &N, &row_ptr, &col_idx, &val);
  read_graph_from_file("web-stanford.txt", &N, &row_ptr, &col_idx, &val);


  double *scores = malloc(N*sizeof(double));

  start = omp_get_wtime();
  PageRank_iterations(N, row_ptr, col_idx, val, d, epsilon, scores);
  stop = omp_get_wtime();
  time_spent = (double)(stop - start);
  printf("PageRank_iterations with %d nodes: %f s\n", N, time_spent);

  start = omp_get_wtime();
  top_n_webpages(N, scores, n);
  stop = omp_get_wtime();
  time_spent = (double)(stop - start);
  printf("top_n_webpages with %d nodes: %f s\n", N, time_spent);

  free(row_ptr);
  free(col_idx);
  free(val);
  free(scores);
  return 0;
}
