#include "mpi.h"
#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef const char * const ch;

int count_occurrence(ch text_string, ch pattern){
  int i, val, count = 0;
  const int n1 = strlen(text_string);
  const int n2 = strlen(pattern);

  for (i=0; i<n1-n2+1; i++){
    val = strncmp(&(text_string[i]), pattern, n2);
    if (val == 0)
      count ++;
  }
  return count;
}

int count_occurrence_OpenMP(ch text_string, ch pattern){
  int i, val, count = 0;
  const int n1 = strlen(text_string);
  const int n2 = strlen(pattern);

  # pragma omp parallel for reduction(+: count)
  for (i=0; i<n1-n2+1; i++){
    val = strncmp(&(text_string[i]), pattern, n2);
    if (val == 0)
      count ++;
  }
  return count;
}

/*
int parallel_count_occurance(ch text_string, ch pattern)
{
  int n1, n2;
  char *my_text_string, *my_pattern;

  const bool i_am_root = (my_rank == 0);
  if (i_am_root){
    n1 = strlen(text_string);
    n2 = strlen(pattern);
  }
  MPI_Bcast (&n1, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast (&n2, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // TODO: root can use the full array if desired,
  // does not need to alloc my_text_string and pattern

  my_text_string = malloc(n1*sizeof(char)); // WRONG
  my_pattern = malloc(n2*sizeof(char));

  // TODO: root sends data to all other procs

  // TODO: each proc calculates their count

  // TODO: each proc sends their count to root

  // TODO: memory dealloc

  return 0;
}

int MPI_main(int argc, char *argv[]) {
  int my_rank, num_procs;
  char *text_string, *pattern;

  MPI_Init (&argc, &argv);

  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

  const bool i_am_root = (my_rank == 0);

  if (i_am_root){
    text_string = "ATTTGCGCAGACCTAAGCA";
    pattern = "GCA";
  }

  if (parallel_count_occurance(my_text_string, my_pattern) == 2)
    printf("Yay\n");
  else
    printf("Nay\n");


  MPI_Finalize();

  return 0;
}
*/

void match(const int a, const int b)
{
  if (a == b)
    printf("Yay\n");
  else
    printf("Nay\n");
}

int main(int argc, char const *argv[]) {
  match(count_occurrence("ATTTGCGCAGACCTAAGCA", "GCA"), 2);
  match(count_occurrence_OpenMP("ATTTGCGCAGACCTAAGCA", "GCA"), 2);

  return 0;
}
