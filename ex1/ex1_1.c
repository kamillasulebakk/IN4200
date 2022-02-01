#include <stdio.h>
#include <math.h>
#include <time.h>

int lim_1 () {
  float sum = 1;
  for (int i=2; i<1000; i+=4)
    sum = sum - 1/pow(2,i);
  for (int j=4; j<1000; j+=4)
    sum = sum + 1/pow(2,j);

  printf("%f\n", sum);

  return 0;
}

int lim_2() {
  float sum = 0;
  float add = 1;
  for (int i=0; i<500; i++) {
    sum += add;
    add *= -0.25;
  }

  printf("%f\n", sum);

  return 0;
}

int main() {
  double time_spent = 0.0;
  clock_t start, stop;
  start = clock();
  lim_1();
  stop = clock();
  time_spent = (double)(stop - start)/CLOCKS_PER_SEC;
  printf("lim_1: %f s\n", time_spent);

  start = clock();
  lim_2();
  stop = clock();
  time_spent = (double)(stop - start)/CLOCKS_PER_SEC;
  printf("lim_2: %f s\n", time_spent);

  return 0;
}
