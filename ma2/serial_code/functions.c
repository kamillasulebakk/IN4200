#include "functions.h"

void allocate_image(image *u, int m, int n)
{
  u->m = m;
  u->n = n;

  u->image_data = malloc(m*sizeof(float *));
  u->image_data[0] = malloc(m*n*sizeof(float));
  for (size_t i = 1; i < m; i++)
    u->image_data[i] = &(u->image_data[i-1][n]);
}

void deallocate_image(image *u)
{
  free(u->image_data[0]);
  free(u->image_data);
}

void convert_jpeg_to_image(const unsigned char* image_chars, image *u)
{
  const int m = u->m;
  const int n = u->n;

  for (size_t i = 0; i < m; i++)
    for (size_t j = 0; j < n; j++)
      u->image_data[i][j] = image_chars[i*n + j];
}

void convert_image_to_jpeg(const image *u, unsigned char* image_chars)
{
  const int m = u->m;
  const int n = u->n;

  for (size_t i = 0; i < m; i++)
    for (size_t j = 0; j < n; j++)
      image_chars[i*n + j] = u->image_data[i][j];
}

void swap(image *u, image *u_bar)
{
  image *temp = u;
  u = u_bar;
  u_bar = temp;
}

void iso_diffusion_denoising(image *u, image *u_bar, float kappa, const int iters)
{
  const int m = u->m;
  const int n = u->n;

  for (size_t i = 0; i < m; i++){
    u_bar->image_data[i][0] = u->image_data[i][0];
    u_bar->image_data[i][n-1] = u->image_data[i][n-1];
  }

  for (size_t j = 0; j < n; j++){
    u_bar->image_data[0][j] = u->image_data[0][j];
    u_bar->image_data[m-1][j] = u->image_data[m-1][j];
  }

  for (size_t count = 0; count < iters; count++){
    for (size_t i = 1; i < m - 1; i++)
      for (size_t j = 1; j < n - 1; j++)
        u_bar->image_data[i][j] = u->image_data[i][j]
                      + kappa*(u->image_data[i-1][j]
                              + u->image_data[i][j-1] - 4*u->image_data[i][j]
                              + u->image_data[i][j+1] + u->image_data[i+1][j]);
    swap(u, u_bar);
  }

  if (iters % 2 == 1)
    swap(u, u_bar);
}
