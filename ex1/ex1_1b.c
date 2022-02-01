#include <stdlib.h>
#include <stdio.h>

int some_function(int n) {
  int * rand_arr = malloc(n*sizeof(int));
  int i, min, max;
  for (i=0; i<n; i++)
    rand_arr[i] = rand();
  min=max=rand_arr[0];
  for (i=0; i<n; i++){
    if (min>rand_arr[i])
      min=rand_arr[i];
    if (max<rand_arr[i])
      max=rand_arr[i];
    }

  printf("max value: %d\n", max);
  printf("min value: %d\n", min);

  free(rand_arr);
  return 0;
}


int main() {
  some_function(20);

  return 0;
}
