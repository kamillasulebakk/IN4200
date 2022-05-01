#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "../simple-jpeg/import_export_jpeg.h"

int main(int argc, char *argv[])
{
  int m, n, c, iters;
  int my_rank, num_procs;
  float kappa;
  image u, u_bar;
  unsigned char *image_chars, *my_image_chars;
  char *input_jpeg_filename, *output_jpeg_filename;
  int *send_counts, *Sdispls;

  MPI_Init (&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

  const bool i_am_root = (my_rank == 0);

  kappa = 0.1; //atof(argv[1]);
  iters = 5; //atoi(argv[2]);
  input_jpeg_filename = "noisy_mona_lisa.jpg"; // argv[3];
  output_jpeg_filename = "denoised_mona_lisa.jpg"; // argv[4];

  if (i_am_root)
    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);

  MPI_Bcast (&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast (&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

  const int my_m = calculate_my_m(my_rank, num_procs, m);

  if (i_am_root)
    calculate_counts_and_displacement(&send_counts, &Sdispls, num_procs, m, n);

  my_image_chars = malloc(my_m*n*sizeof(unsigned char));

  MPI_Scatterv(
    image_chars, send_counts, Sdispls, MPI_INT,
    my_image_chars, my_m*n, MPI_INT, 0, MPI_COMM_WORLD
  );

  allocate_image (&u, my_m, n);
  allocate_image (&u_bar, my_m, n);

  convert_jpeg_to_image (my_image_chars, &u);
  iso_diffusion_denoising_parallel (&u, &u_bar, kappa, iters);

  /* each process sends its resulting content of u_bar to process 0 */
  /* process 0 receives from each process incoming values and */
  /* copy them into the designated region of struct whole_image */
  /* ... */
  // MPI_Gather(my_length, 1, MPI_INT, num_rows[my_rank], 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (i_am_root) {
    export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
  }

  deallocate_image (&u);
  deallocate_image (&u_bar);
  free(send_counts); free(Sdispls);
  MPI_Finalize ();

  return 0;
}


// mpirun -np 4 ./a.out
// here 4 stands for 4 processors
