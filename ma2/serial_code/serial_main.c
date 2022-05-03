#include <stdio.h>

#ifdef __MACH__
#include <stdlib.h>
#else
#include <malloc.h>
#endif

#include "functions.h"
#include "../simple-jpeg/import_export_jpeg.h"

int main(int argc, char *argv[])
{
  int m, n, c;
  image u, u_bar;
  unsigned char *image_chars;
  char *input_jpeg_filename, *output_jpeg_filename;

  const float kappa = atof(argv[1]);
  const int iters = atoi(argv[2]);
  input_jpeg_filename = "../img/noisy_mona_lisa.jpg"; // argv[3];
  output_jpeg_filename = "../img/denoised_mona_lisa_serial_2.jpg"; // argv[4];

  import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
  printf("Succeeded! vertical pixels: %d, horizontal pixels: %d, num components: %d\n",
	 m, n, c);

  allocate_image (&u, m, n);
  allocate_image (&u_bar, m, n);
  convert_jpeg_to_image (image_chars, &u);

  iso_diffusion_denoising (&u, &u_bar, kappa, iters);

  convert_image_to_jpeg (&u_bar, image_chars);
  export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);

  free(image_chars);
  deallocate_image (&u);
  deallocate_image (&u_bar);

  return 0;
}
