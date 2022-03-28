#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

void read_graph_from_file (char *filename, int *N, int **row_ptr, int **col_idx, double **val);
void PageRank_iterations (int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores);
void top_n_webpages (int N, double *scores, int n);

int main(int argc, char const *argv[]) {
  double time_spent = 0.0;
  clock_t start, stop;

  int N=0, *row_ptr, *col_idx;
  double *val;
  double d=0.85, epsilon=1e-6;
  int n = 3;

  // read_graph_from_file("simple-webgraph.txt", &N, &row_ptr, &col_idx, &val);
  // read_graph_from_file("simple-webgraph-invalid.txt", &N, &row_ptr, &col_idx, &val);
  read_graph_from_file("100-webgraph.txt", &N, &row_ptr, &col_idx, &val);
  // read_graph_from_file("web-stanford.txt", &N, &row_ptr, &col_idx, &val);


  double *scores = malloc(N*sizeof(double));

  start = clock();
  #pragma omp parallel
  {
    PageRank_iterations(N, row_ptr, col_idx, val, d, epsilon, scores);
  }
  stop = clock();
  time_spent = (double)(stop - start)/CLOCKS_PER_SEC;
  printf("PageRank_iterations: %f s\n", time_spent);

  start = clock();
  top_n_webpages(N, scores, n);
  stop = clock();
  time_spent = (double)(stop - start)/CLOCKS_PER_SEC;
  printf("top_n_webpages: %f s\n", time_spent);

  free(row_ptr);
  free(col_idx);
  free(val);
  free(scores);
  return 0;
}
