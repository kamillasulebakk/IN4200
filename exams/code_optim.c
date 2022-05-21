#include <string.h>

void slow()
{
  for (int i=0; i<n; i++) {
    c[i] = exp(1.0*i/n)+sin(3.1415926*i/n);
    for (int j=0; j<n; j++)
      a[j][i] = b[j][i] + d[j]*e[i];
  }
}

void faster()
{
  for (int i=0; i<n; i++) {
    c[i] = exp(1.0*i/n)+sin(3.1415926*i/n);

  for (size_t i = 0; i < n; i++)
    for (int j=0; j<n; j++)
      a[i][j] = b[i][j] + d[i]*e[j];
}

void fasterer()
{
  for (int i=0; i<n; i+=4) {
    c[i] = exp(1.0*i/n)+sin(3.1415926*i/n);

  for (size_t i = 0; i < n; i++){
    for (int j=0; j<n; j++){
      a[i][j] = b[i][j] + d[i]*e[j];
      a[i+1][j] = b[i+1][j] + d[i+1]*e[j];
      a[i+2][j] = b[i+2][j] + d[i+2]*e[j];
      a[i+3][j] = b[i+3][j] + d[i+3]*e[j];
    }
  }

  for (int i=n-(n%4); i<n; i++){
    for (int j=0; j<n; j++){
      a[i][j] = b[i][j] + d[i]*e[j];
    }
  }
}

