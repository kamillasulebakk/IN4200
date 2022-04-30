#include "functions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void allocate_image(image *u, int m, int n)
{
  u->m = m;
  u->n = n;

  u->image_data = malloc(m*sizeof(float *));
  // for each row, malloc space for its column elements and add it to
  // the array of arrays
  for (size_t i = 0; i < m; i++) {
  // malloc space for row i's m column elements
      u->image_data[i] = malloc(n*sizeof(float));
  }
}

void deallocate_image(image *u)
{
  int m = u->m;

  for (size_t i = 0; i < m; i++){
    free(u->image_data[i]);
  }
  free(u->image_data);
}

void convert_jpeg_to_image(const unsigned char* image_chars, image *u)
{
  int m = u->m;
  int n = u->n;

  for (size_t i = 0; i < m; i++){
    for (size_t j = 0; j < n; j++){
      u->image_data[i][j] = image_chars[i*n + j];
    }
  }
}

void convert_image_to_jpeg(const image *u, unsigned char* image_chars)
{
  int m = u->m;
  int n = u->n;

  for (size_t i = 0; i < m; i++){
    for (size_t j = 0; j < n; j++){
      image_chars[i*n + j] = u->image_data[i][j];
    }
  }
}

void iso_diffusion_denoising_parallel(image *u, image *u_bar, float kappa, int iters)
{
printf("hello\n");
}