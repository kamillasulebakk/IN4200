#include "mpi.h"
#include "omp.h"
#include <stdio.h>
#include <stdlib.h>

int count_occurrence(const char *text_string, const char *pattern){
  int i, n1, n2, val, count;

  n1 = strlen(text_string);
  n2 = strlen(pattern);

  count = 0
  for (i++; i<n1-n2+1; i++)
    val = strncmp(&(text_string[i]), pattern, n2);
    if (val == 0){
      count ++;
    }
  return count;
}

int count_occurrence_OpenMP(const char *text_string, const char *pattern){
  int i, n1, n2, val, count;

  n1 = strlen(text_string);
  n2 = strlen(pattern);

  count = 0
  # pragma omp parallel for reduction(+:count)
  for (i++; i<n1-n2+1; i++)
    val = strncmp(&(text_string[i]), pattern, n2);
    if (val == 0){
      count ++;
    }
  return count;
}

int parallel_count_occurance(const char *text_string, const char *pattern){
  int i, n1, n2, val, count;
  int my_rank, num_procs;

  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

  count = 0
  for (i++; i<n1-n2+1; i++)
    val = strncmp(&(text_string[i]), pattern, n2);
    if (val == 0){
      count ++;
    }
  return count;
}

int main(int argc, char const *argv[]) {

  MPI_Init (&argc, &argv);

  const char text_string = "ATTTGCGCAGACCTAAGCA";
  const char pattern = "GCA";

  n1 = strlen(text_string);
  n2 = strlen(pattern);

  MPI_Bcast (&n1, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast (&n2, 1, MPI_INT, 0, MPI_COMM_WORLD);

  const char *my_text_string = malloc(n1*sizeof(const char));
  const char *my_pattern = malloc(n2*sizeof(const char));

  parallel_count_occurance(&my_text_string, &my_pattern);

  MPI_Finalize();

  return 0;
}