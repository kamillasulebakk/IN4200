#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "omp.h"

void print_array_i(const int * const a, const int N)
{
  for (size_t i = 0; i < N; i++)
    printf(" %d\n", a[i]);
  printf("\n");
}

int compare_exchange(int *v1, int *v2)
{
  if (*v1 > *v2){
    const int tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
    return 1;
  }
  return 0;
}

void serial_bubble_sort(int n, int *a) {
  int count = 0;
  int iter = 0;
  for (int i=(n-2); i>=0; i--){
    for (int j=0; j<=i; j++){
      if(compare_exchange(&(a[j]), &(a[j+1])))
        count++;
    }
    if (count == 0){
      break;
    }else{
      count = 0;
      iter ++;
    }
  }
  printf("iterations: %d\n", iter);
}

void oddeven_sort(const int N, int *a)
{
  int i, j, count, prev_count=1;
  bool even_iteration, last_two_counts_zero;
  for (i=0; i<N; i++){
    count = 0;
    even_iteration = (i%2 == 0);
    if (even_iteration){
      for (j=0; j<N/2; j++)
        if (compare_exchange(&(a[2*j]), &(a[2*j+1])))
          count++;
    } else {
      for (j=0; j<N/2-1; j++)
        if (compare_exchange(&(a[2*j+1]), &(a[2*j+2])))
          count++;
    }

    last_two_counts_zero = (count + prev_count == 0);
    if (last_two_counts_zero){
      printf("Breaking at iteration %d\n", i);
      break;
    }
    prev_count = count;
  }
}
// /*
void para_oddeven_sort(const int n, int *a) {
  int i, j, count, prev_count;
  bool last_two_counts_zero;

  #pragma omp parallel private(i, j, last_two_counts_zero, prev_count)
  {
  for (i=0; i<n; i++){
    count = 0;
    if (i%2 == 0){
      #pragma omp for reduction(+:count)
      for (j=0; j<(n/2); j++)
        if(compare_exchange(&(a[2*j]), &(a[2*j+1])))
          count++;
    }else{
      #pragma omp for reduction(+:count)
      for (j=0; j<(n/2)-1; j++)
        if(compare_exchange(&(a[2*j+1]), &(a[2*j+2])))
          count++;
    }

    last_two_counts_zero = (count + prev_count == 0);
    if (last_two_counts_zero){
      printf("Breaking at iteration %d\n", i);
      break;
    }
    prev_count = count;
  } // end of for loop
  } // end of parallel region
} // end of function
// */

int main(int argc, char const *argv[]) {
  const int n = 14;
  int numbers[] = { 1, 5, 2, 7, 5, 9, 2, 9, -3, -1, 1, 6, 3, 10 };
  int *a = malloc(n*sizeof(int));
  for (size_t i = 0; i < n; i++)
    a[i] = numbers[i];

  // serial_bubble_sort(n, a);
  // print_array_i(a, n);
  print_array_i(a, n);

  oddeven_sort(n, a);
  print_array_i(a, n);

  return 0;
}