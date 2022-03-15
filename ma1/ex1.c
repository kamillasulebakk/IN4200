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
  read_graph_from_file("simple-webgraph.txt", &N, &row_ptr, &col_idx, &val);
  return 0;
}

/*
This function reads a text file that contains a web graph, so that the
corresponding hyperlink matrix is built up in the CRS forma
*/
void read_graph_from_file (char *filename, int *N, int **row_ptr, int **col_idx, double **val){
  int edges = 0;
  int FromNodeId, ToNodeId;
  FILE *fp = fopen(filename, "r");
  double **hyper_mat;

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

  printf("%d %d\n", *N, edges);

  int *fromID = malloc(edges*sizeof(int));
  int *toID = malloc(edges*sizeof(int));
  int *arr = malloc((*N)*sizeof(int));


  for (size_t i=0; i<edges; i++){
    fscanf(fp, "%d %d", &(fromID[i]), &(toID[i]));
    arr[fromID[i]]++;
  }

  zeros2D(&hyper_mat, *N, *N);
  // printmat(hyper_mat, *N, *N);
  printvec_i(arr, *N);

  for (size_t i=0; i<edges; i++)
    hyper_mat[toID[i]][fromID[i]] = 1.0 / (double) arr[fromID[i]];

  printmat(hyper_mat, *N, *N);

  int *val = malloc((*N)*sizeof(int));

  for (size_t i=0; i<(*N); i++){
    for (size_t j=0; j<(*N); j++){
      if (hyper_mat[i][j] != 0){

      }
    }
  }



  free2D(hyper_mat);
  free(arr);

  // close the file
  fclose(fp);
}


