#include <stdio.h>

#ifdef __MACH__
#include <stdlib.h>
#else
#include <malloc.h>
#endif

#include "functions.h"

void allocate_image(image *u, int m, int n);
void deallocate_image(image *u);
void convert_jpeg_to_image(const unsigned char* image_chars, image *u);
void convert_image_to_jpeg(const image *u, unsigned char* image_chars);
void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters);

void import_JPEG_file (const char* filename, unsigned char** image_chars,
                       int* image_height, int* image_width,
                       int* num_components);
void export_JPEG_file (const char* filename, const unsigned char* image_chars,
                       int image_height, int image_width,
                       int num_components, int quality);

int main(int argc, char *argv[])
{
  int m, n, c, iters;
  float kappa;
  image u, u_bar;
  unsigned char *image_chars;
  char *input_jpeg_filename, *output_jpeg_filename;

  kappa = 0.1; //atof(argv[1]);
  iters = 5; //atoi(argv[2]);
  input_jpeg_filename = "noisy_mona_lisa.jpg"; // argv[3];
  output_jpeg_filename = "denoised_mona_lisa.jpg"; // argv[4];

  import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
  printf("Succeeded! vertical pixels: %d, horizontal pixels: %d, num components: %d\n",
	 m, n, c);

  allocate_image (&u, m, n);
  allocate_image (&u_bar, m, n);
  convert_jpeg_to_image (image_chars, &u);

  iso_diffusion_denoising (&u, &u_bar, kappa, iters);

  convert_image_to_jpeg (&u_bar, image_chars);
  export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);

  deallocate_image (&u);
  deallocate_image (&u_bar);

  printf("hello\n");

  return 0;
}
