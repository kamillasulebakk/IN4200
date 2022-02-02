#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define CLOCKS_TO_MILLISEC(t) (t*1000)/CLOCKS_PER_SEC


int main(int argc, char const *argv[]) {
  clock_t start, stop, timer;
  int n = 100000;
  double * a = malloc(n*sizeof(double));
  double * b = malloc(n*sizeof(double));

  for (int i=0; i<n; i++){
    a[i] = i;
    b[i] = 2*i;
  }

  start = clock();
  for (int i=0; i<n; i++)
    b[i] = a[i];
  stop = clock();
  timer = stop - start;

  // printf("array a \n");
  // for (int i=0; i<n; i++)
  //   printf("%f\n", a[i]);

  // printf("array b \n");
  // for (int i=0; i<n; i++)
  //   printf("%f\n", b[i]);

  printf("hand-code: %ld\n", timer);

  start = clock();
  memcpy(b, a, n*sizeof *a);
  stop = clock();
  timer = stop - start;
  printf("memory_copy: %ld\n", timer);

  free(a);
  free(b);

  return 0;
}
