#include <stdio.h>
/*
#include <math.h>

int main(int argc, char const *argv[]) {
  float sum = 1;
  for (int i=2; i<1000; i+=4)
    sum = sum - 1/pow(2,i);
  for (int j=4; j<1000; j+=4)
    sum = sum + 1/pow(2,j);

  printf("%f\n", sum);

  return 0;
}
*/
int main(int argc, char const *argv[]) {
  float sum = 0;
  float add = 1;
  for (int i=0; i<500; i++) {
    sum += add;
    add *= -0.25;
  }

  printf("%f\n", sum);

  return 0;
}
