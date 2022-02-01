#include <stdlib.h>

int main(int argc, char const *argv[]) {
  float sum = 0;
  for (int i=0; i<1000; i+=2)
    sum = sum + 1/pow(2,i);
  printf("%f\n", sum);
  
  return 0;
}
