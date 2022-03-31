#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

void read_graph_from_file (const char *filename, int *N, int **row_ptr, int **col_idx, double **val);
void PageRank_iterations (int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores);
void top_n_webpages (int N, double *scores, int n);

int main(int argc, char const *argv[]) {
  double time_spent = 0.0;
  double start, stop;
  clock_t start_time, stop_time;

  int N=0, *row_ptr, *col_idx;
  double *val;

  const char *filename;
  double d;
  double epsilon;
  int n;

  if (argc == 5){
    filename = argv[1];
    d = atof(argv[2]);
    epsilon = atof(argv[3]);
    n = atoi(argv[4]);
  }

  else{
    printf("Please specify filename, d, epsilon and n!\n");
    return 1;
  }

  start = clock();
  read_graph_from_file(filename, &N, &row_ptr, &col_idx, &val);
  stop = clock();
  time_spent = (double)(stop - start)/CLOCKS_PER_SEC;
    printf("\nRunning program with %d nodes \n", N);
  printf("\nread_graph_from_file finished in %f s\n", time_spent);

  double *scores = malloc(N*sizeof(double));

  start = omp_get_wtime();
  PageRank_iterations(N, row_ptr, col_idx, val, d, epsilon, scores);
  stop = omp_get_wtime();
  time_spent = (double)(stop - start);
  printf("\nPageRank_iterations finished in %f s\n", time_spent);

  start = omp_get_wtime();
  top_n_webpages(N, scores, n);
  stop = omp_get_wtime();
  time_spent = (double)(stop - start);
  printf("\ntop_n_webpages finished in %f s\n", time_spent);

  free(row_ptr);
  free(col_idx);
  free(val);
  free(scores);

  return 0;
}
