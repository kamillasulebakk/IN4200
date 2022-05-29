#include "mpi.h"
#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef const char * const ch;
typedef const int cint;

int count_occurrence(ch text_string, ch pattern){
  int i, val, count = 0;
  cint n1 = strlen(text_string);
  cint n2 = strlen(pattern);

  for (i=0; i<n1-n2+1; i++){
    val = strncmp(&(text_string[i]), pattern, n2);
    if (val == 0)
      count ++;
  }
  return count;
}

int count_occurrence_OpenMP(ch text_string, ch pattern){
  int i, val, count = 0;
  cint n1 = strlen(text_string);
  cint n2 = strlen(pattern);

  # pragma omp parallel for reduction(+: count)
  for (i=0; i<n1-n2+1; i++){
    val = strncmp(&(text_string[i]), pattern, n2);
    if (val == 0)
      count ++;
  }
  return count;
}

int overlap_beside(cint rank, cint num_procs, cint n2)
{
  return (n2 - 1)*(rank != (num_procs - 1));
}

int residue(cint rank, cint num_procs, cint n1)
{
  return (rank < n1%num_procs);
}

int calculate_my_length(cint rank, cint num_procs, cint n1, cint n2)
{
  return n1/num_procs + residue(rank, num_procs, n1) + overlap_beside(rank, num_procs, n2);
}

void calculate_counts_and_displacement(cint num_procs, cint n1, cint n2, int **sendcounts, int **displs)
{
  *sendcounts = malloc(num_procs*sizeof(int));
  *displs = malloc(num_procs*sizeof(int));
  (*displs)[0] = 0;
  for (size_t i = 0; i < num_procs; i++) {
    (*sendcounts)[i] = calculate_my_length(i, num_procs, n1, n2);
  }
  for (size_t i = 1; i < num_procs; i++){
    (*displs)[i] = (*displs)[i-1] + sendcounts[i-1] - overlap_beside(i-1, num_procs, n2);
  }
}

int count_occurrence_MPI(ch text_string, ch pattern)
{
  int n1, n2, count;
  char *my_text_string, *my_pattern;
  int *sendcounts, *displs;
  MPI_Request request;
  MPI_Status status;

  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

  const bool i_am_root = (my_rank == 0);
  if (i_am_root){
    n1 = strlen(text_string);
    n2 = strlen(pattern);
  }
  MPI_Bcast (&n1, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast (&n2, 1, MPI_INT, 0, MPI_COMM_WORLD);

  cint my_n1 = calculate_my_length(my_rank, num_procs, n1, n2);

  if (i_am_root){
    calculate_counts_and_displacement(num_procs, n1, n2, &sendcounts, &displs);
  }

  my_text_string = malloc(my_n1*sizeof(char));
  MPI_Scatterv (text_string, send_counts, displs, MPI_CHAR, my_text_string, my_n1, MPI_CHAR, 0, MPI_COMM_WORLD);

  my_pattern = malloc(n2*sizeof(char));
  MPI_Bcast (my_pattern, n2, MPI_CHAR, 0, MPI_COMM_WORLD);

  int my_count = count_occurrence(my_text_string, my_pattern);

  printf("Process %d found %d\n", my_rank, my_count);

  MPI_Reduce (my_count, count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  free(my_pattern);
  free(my_text_string);

  return count;
}

void match(cint a, cint b)
{
  if (a == b)
    printf("Yay\n");
  else
    printf("Nay\n");
}

int MPI_main(int argc, char *argv[]) {
  int my_rank, num_procs;
  char *text_string, *pattern;

  MPI_Init (&argc, &argv);

  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

  const bool i_am_root = (my_rank == 0);

  if (i_am_root){
    text_string = "ATTTGCGCAGACCTAAGCAHJALSDLJASDGCAGGHLAJSHFLJASHFASGCAGCA";
    pattern = "GCA";
  }

  int MPI_count = count_occurrence_MPI;
  if (i_am_root)
    match(MPI_count, 5);

  MPI_Finalize();

  return 0;
}

int main(int argc, char const *argv[]) {
  // match(count_occurrence("ATTTGCGCAGACCTAAGCA", "GCA"), 2);
  // match(count_occurrence_OpenMP("ATTTGCGCAGACCTAAGCA", "GCA"), 2);

  MPI_main(argc, argv);

  return 0;
}
