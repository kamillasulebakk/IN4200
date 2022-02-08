#include <stdio.h>
#include <time.h>
#include <math.h>

double pow_function(double x, double y){
  int i = 1;
  double sum = x;
  while (i < y){
    sum = sum*x;
    i += 1;
  }
  return sum;
}

double pow_function_v2(double x){
  double x4, x32, xp;
  xp = x*x; // x^2
  xp *= xp;  // x^4
  x4 = xp;
  xp *= xp; // x^8
  xp *= xp; // x^16
  xp *= xp; // x^32
  x32 = xp;
  xp *= xp; // x^64

  return (x4*x32*xp); //x^(4+32+64)
}


int main(int argc, char const *argv[]) {
  clock_t start, stop, pow_timer;
  double sum;
  double x = 1.5, y = 100;

  start = clock();
  sum = pow_function(x, y);
  stop = clock();
  pow_timer = (double)(stop - start);
  printf("%f\n", sum);
  printf("Time pow own function: %lu \n", pow_timer);

  start = clock();
  sum = pow_function_v2(x);
  stop = clock();
  pow_timer = (double)(stop - start);
  printf("%f\n", sum);
  printf("Time pow own function v2: %lu \n", pow_timer);

  start = clock();
  sum = pow(x, y);
  stop = clock();
  pow_timer = (double)(stop - start);
  printf("%f\n", sum);
  printf("Time pow library function: %lu \n", pow_timer);

  return 0;
}