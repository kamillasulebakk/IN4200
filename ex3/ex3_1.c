#include <stdio.h>
#include <time.h>


double numerical_integration (double x_min, double x_max, int slices){
  double delta_x = (x_max-x_min)/slices;
  double x, sum = 0.0;
  for (int i=0; i<slices; i++){
    x = x_min + (i+0.5)*delta_x;
    sum = sum + 4.0/(1.0+x*x);
  }
  return sum*delta_x;
}

int main(int argc, char const *argv[]) {
  int n_div = 100;
  double result;
  result = numerical_integration(0.0, 1.0, n_div);
  printf("%f\n", result);

  // counting cycles.
  unsigned long long start = __rdtsc();
  result = numerical_integration(0.0, 1.0, n_div);
  unsigned long long end = __rdtsc();

  double avg = (double)(end - start)/n_div;

  printf("Average number of cycles: %lf\n", avg);
  return 0;
}
