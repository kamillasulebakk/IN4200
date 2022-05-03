#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

bool test_calculate_counts_and_displacement_1()
{
  const int m = 5;
  const int n = 4;
  const int num_procs = 1;
  int *counts, *disp;
  calculate_counts_and_displacement(&counts, &disp, num_procs, m, n);
  const int counts_correct[] = {5*4};
  const int disp_correct[] = {0};

  bool result = true;
  for (int rank=0; rank<num_procs; rank++) {
    if (counts[rank] != counts_correct[rank])
      result = false;
    if (disp[rank] != disp_correct[rank])
      result = false;
  }

  free(counts); free(disp);

  return result;
}

bool test_calculate_counts_and_displacement_2()
{
  const int m = 6;
  const int n = 4;
  const int num_procs = 2;
  int *counts, *disp;
  calculate_counts_and_displacement(&counts, &disp, num_procs, m, n);
  const int counts_correct[] = {4*4, 4*4};
  const int disp_correct[] = {0, 2*4};

  bool result = true;
  for (int rank=0; rank<num_procs; rank++) {
    if (counts[rank] != counts_correct[rank])
      result = false;
    if (disp[rank] != disp_correct[rank])
      result = false;
  }

  free(counts); free(disp);

  return result;
}

bool test_calculate_counts_and_displacement_3()
{
  const int m = 6;
  const int n = 4;
  const int num_procs = 3;
  int *counts, *disp;
  calculate_counts_and_displacement(&counts, &disp, num_procs, m, n);
  const int counts_correct[] = {3*4, 4*4, 3*4};
  const int disp_correct[] = {0, 1*4, 3*4};

  bool result = true;
  for (int rank=0; rank<num_procs; rank++) {
    if (counts[rank] != counts_correct[rank])
      result = false;
    if (disp[rank] != disp_correct[rank])
      result = false;
  }

  free(counts); free(disp);

  return result;
}

bool test_calculate_counts_and_displacement_4()
{
  const int m = 14;
  const int n = 7;
  const int num_procs = 4;
  int *counts, *disp;
  calculate_counts_and_displacement(&counts, &disp, num_procs, m, n);
  const int counts_correct[] = {4*n, 6*n, 5*n, 5*n};
  const int disp_correct[] = {0, 2*n, 6*n, 9*n};

  bool result = true;
  for (int rank=0; rank<num_procs; rank++) {
    if (counts[rank] != counts_correct[rank])
      result = false;
    if (disp[rank] != disp_correct[rank])
      result = false;
  }

  free(counts); free(disp);

  return result;
}

bool test_calculate_counts_and_displacement()
{
  bool result = true;
  if (!test_calculate_counts_and_displacement_1())
    result = false;
  if (!test_calculate_counts_and_displacement_2())
    result = false;
  if (!test_calculate_counts_and_displacement_3())
    result = false;
  if (!test_calculate_counts_and_displacement_4())
    result = false;
    
  return result;
}

int main()
{
  bool success = test_calculate_counts_and_displacement();
  if (success)
    printf("All tests passed\n");
  else
    printf("Tests failed\n");

  return 0;
}
