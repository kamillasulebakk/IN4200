#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void read_file(int *len, float **temperatures, int **times){
  int hour, minute;
  float temp;
  char *filename = "temperature.txt";
  FILE *fp = fopen(filename, "r");

  if (fp == NULL){
    printf("Error: could not open file %s", filename);
    exit(0);
  }

  fscanf(fp, "%d", len);
  *times = malloc((*len)*sizeof(int));
  *temperatures = malloc((*len)*sizeof(float));

  for (int i=0; i<(*len); i++){
    fscanf(fp, "%d:%d %f", &hour, &minute, &temp);
    (*times)[i] = hour*60 + minute;
    (*temperatures)[i] = temp;
  }

  // close the file
  fclose(fp);
}

float average(int len, float *a){
  float avg = 0.0;
  for (int i=0; i<len; i++)
    avg += a[i];
  avg /= len;

  return avg;
}

float standard_deviation(int len, float avg, float *a){
  float SD = 0.0;
  for (int i=0; i < len; i++){
    SD += (a[i] - avg)*(a[i] - avg);
  }
  return sqrt(SD/len);
}

void minmax(float *min, float *max, int len, float *a){
  (*min)=(*max)=a[0];
  for (int i=0; i<len; i++){
    if ((*min)>a[i])
      (*min)=a[i];
    if ((*max)<a[i])
      (*max)=a[i];
    }
}

int main(int argc, char const *argv[]) {
  int len, *times;
  float *temperatures, avg, SD, min, max;

  read_file(&len, &temperatures, &times);

  avg = average(len, temperatures);
  SD = standard_deviation(len, avg, temperatures);

  minmax(&min, &max, len, temperatures);

  printf("Length: %d\n", len);
  /*for (int i=0; i<len; i++)
    printf("%10d %10.1f\n", times[i], temperatures[i]); */
  printf("Average: %f\n", avg);
  printf("Standard deviatioin: %f\n", SD);
  printf("Min: %f\n", min);
  printf("Max: %f\n", max);

  free(temperatures);
  free(times);
  return 0;
}

// would be better to make only one function to find average, min, max etc.
// in order to use less memory
