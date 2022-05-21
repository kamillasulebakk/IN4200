#include "omp.h"
#include "math.h"

int main()
{
  int i, j, N, sqrt_N;

  char *array = malloc(N);
  array[0] = array[1] = 0;

  #pragma omp parallel for
  for (i=2; i<N; i++)
    array[i] = 1;

  sqrt_N = (int) (sqrt(N));

  for (i=2; i<=sqrt_N; i++){
    if (array[i]){
      #pragma omp parallel for
      for (j=i*i; j<N; j+=i)
        array[j] = 0;
    }
  }

  free (array);

  return 0;
}

void sweep (int N, double **table1, int n, double **mask, double **table2)
{
int i, j, ii, jj;
double temp;

# pragma omp parallel for
for (i = 0; i <= N-n; i++)
  for (j = 0; j <= N-n; j++){
    temp = 0.0;

    for (ii=0; ii<n; ii++)
      for (jj=0; jj<n; jj++)
        temp += table1[i+ii][j+jj]*mask[ii][jj];
    table2[i][j] = temp; 
  }

}