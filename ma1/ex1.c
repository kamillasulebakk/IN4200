#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "methods.h"

void read_graph_from_file (char *filename, int *N, int **row_ptr, int **col_idx, double **val);
void PageRank_iterations (int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores);
void top_n_webpages (int N, double *scores, int n);

int main(int argc, char const *argv[]) {
  int N=0, *row_ptr, *col_idx;
  double *val;
  // read_graph_from_file("simple-webgraph.txt", &N, &row_ptr, &col_idx, &val);
  read_graph_from_file("simple-webgraph-invalid.txt", &N, &row_ptr, &col_idx, &val);
  free(row_ptr);
  free(col_idx);
  free(val);
  return 0;
}

/*
This function reads a text file that contains a web graph, so that the
corresponding hyperlink matrix is built up in the CRS forma
*/
void read_graph_from_file (char *filename, int *N, int **row_ptr, int **col_idx, double **val){
  int fromVal, toVal, invalid_entries = 0, edges = 0;
  size_t i, start, stop;

  FILE *fp = fopen(filename, "r");

  if (fp == NULL){
    printf("Error: could not open file %s", filename);
    exit(0);
  }
  // read past the two leading lines of text
  fscanf(fp, "# %*[^#]");
  fscanf(fp, "# %*[^#]");

  fscanf(fp, "# Nodes: %d Edges: %d " , N, &edges);

  // read past the fourth line
  fscanf(fp, "# FromNodeId    ToNodeId");

  int *fromID = malloc(edges*sizeof(int));
  int *toID = malloc(edges*sizeof(int));
  int *arr = malloc((*N)*sizeof(int));
  for (i = 0; i < *N; i++)
    arr[i] = 0;
  *row_ptr = malloc((*N + 1)*sizeof(int));
  for (i = 0; i < (*N+1); i++)
    (*row_ptr)[i] = 0;

  for (i=0; i<edges; i++){
    fscanf(fp, "%d %d", &fromVal, &toVal);
    if (fromVal != toVal){
      arr[fromVal]++;
      fromID[i - invalid_entries] = fromVal;
      toID[i - invalid_entries] = toVal;
      (*row_ptr)[toVal+1]++;
    }
    else
      invalid_entries++;
  }
  printf("Excluding %d invalid entries\n", invalid_entries);
  edges -= invalid_entries;
  if (invalid_entries > 0) {
    toID = realloc(toID, edges*sizeof(int));
    fromID = realloc(fromID, edges*sizeof(int));
  }

  for (i=1; i<(*N+1); i++)
    (*row_ptr)[i] += (*row_ptr)[i-1];

  sort_inplace(toID, fromID, edges);
  for (i = 0; i < (*N); i++) {
    start = (*row_ptr)[i], stop = (*row_ptr)[i+1];
    sort_inplace(&(fromID[start]), &(toID[start]), stop - start);
  }

  *col_idx = fromID;

  *val = malloc(edges*sizeof(double));
  for (i = 0; i < edges; i++)
    (*val)[i] = 1.0 / (double) arr[(*col_idx)[i]];
  printvec_i(arr, *N);
  printvec_i(*col_idx, edges);
  printvec_d(*val, edges);

  free(arr);
  free(toID);

  // close the file
  fclose(fp);
}


