#include <stdlib.h>
#include <stdio.h>

void read_graph_from_file (char *filename, int *N, int **row_ptr, int **col_idx, double **val);
void PageRank_iterations (int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores);
void top_n_webpages (int N, double *scores, int n);

int main(int argc, char const *argv[]) {
  int N=0, *row_ptr, *col_idx;
  double *val;
  double d=0.85, epsilon=1e-6;
  int n = 3;

  // read_graph_from_file("simple-webgraph.txt", &N, &row_ptr, &col_idx, &val);
  // read_graph_from_file("simple-webgraph-invalid.txt", &N, &row_ptr, &col_idx, &val);
  read_graph_from_file("100-webgraph.txt", &N, &row_ptr, &col_idx, &val);
  double *scores = malloc(N*sizeof(double));

  PageRank_iterations(N, row_ptr, col_idx, val, d, epsilon, scores);

  top_n_webpages(N, scores, n);

  free(row_ptr);
  free(col_idx);
  free(val);
  free(scores);
  return 0;
}
