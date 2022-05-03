#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "functions.h"
#include "utils.h"
#include "../simple-jpeg/import_export_jpeg.h"

int main(int argc, char *argv[])
{
  int m, n, c;
  int my_rank, num_procs;
  image u, u_bar;
  unsigned char *image_chars, *my_image_chars;
  char *input_jpeg_filename, *output_jpeg_filename;
  int *send_counts, *displs;

  MPI_Init (&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

  const bool i_am_root = (my_rank == 0);

  const float kappa = atof(argv[1]);
  const int iters = atoi(argv[2]);
  input_jpeg_filename = "../img/noisy_mona_lisa.jpg"; // argv[3];
  output_jpeg_filename = "../img/denoised_mona_lisa_parallel.jpg"; // argv[4];

  if (i_am_root)
    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);

  MPI_Bcast (&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast (&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

  const int my_m = calculate_my_m(my_rank, num_procs, m);

  if (i_am_root)
    calculate_counts_and_displacement(&send_counts, &displs, num_procs, m, n);

  my_image_chars = malloc(my_m*n*sizeof(unsigned char));

  MPI_Scatterv(
    image_chars, send_counts, displs, MPI_CHAR,
    my_image_chars, my_m*n, MPI_CHAR, 0, MPI_COMM_WORLD
  );

  allocate_image (&u, my_m, n);
  allocate_image (&u_bar, my_m, n);

  convert_jpeg_to_image (my_image_chars, &u);
  iso_diffusion_denoising_parallel (&u, &u_bar, kappa, iters);
  convert_image_to_jpeg(&u_bar, my_image_chars);

  const int rows_to_send = my_m - overlap_above(my_rank) - overlap_below(my_rank, num_procs);
  if (i_am_root)
    edit_counts_and_displs_from_scatter_to_gather(
      send_counts, displs, num_procs, n
    );

  MPI_Gatherv(
    &(my_image_chars[overlap_above(my_rank)*n]), rows_to_send*n, MPI_CHAR,
    image_chars, send_counts, displs, MPI_CHAR, 0, MPI_COMM_WORLD
  );

  if (i_am_root) {
    export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
  }

  deallocate_image (&u);
  deallocate_image (&u_bar);
  free(my_image_chars);
  if (i_am_root){
    free(send_counts);
    free(displs);
    free(image_chars);
  }
  MPI_Finalize ();

  if (i_am_root)
    printf("Done :)\n");

  return 0;
}


// mpirun -np 4 ./a.out
// here 4 stands for 4 processors
