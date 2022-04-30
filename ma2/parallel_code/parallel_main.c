#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../simple-jpeg/import_export_jpeg.h"
#include "functions.h"

/* declarations of functions import_JPEG_file and export_JPEG_file */
int main(int argc, char *argv[])
{
  int m, n, c, iters;
  int my_m, my_n, my_rank, num_procs, my_start, my_stop;
  float kappa;
  image u, u_bar, whole_image;
  unsigned char *image_chars, *my_image_chars;
  char *input_jpeg_filename, *output_jpeg_filename;

  MPI_Init (&argc, &argv);
  // Groupling the different processors according to my wish
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank); // First argument is the communicator you want to find the number of processors in
  MPI_Comm_size (MPI_COMM_WORLD, &num_procs); // For each processor find its unique rank

  kappa = 0.1; //atof(argv[1]);
  iters = 5; //atoi(argv[2]);
  input_jpeg_filename = "noisy_mona_lisa.jpg"; // argv[3];
  output_jpeg_filename = "denoised_mona_lisa.jpg"; // argv[4];

  if (my_rank==0) {
    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
    allocate_image (&whole_image, m, n);
  }

  MPI_Bcast (&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast (&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

  /* 2D decomposition of the m x n pixels evenly among the MPI processes */

  // my_start = (my_rank*m)/num_procs+1;
  // my_stop = ((my_rank+1)*m)/num_procs;
  // my_m = my_stop - my_start + 1;
  // my_n = n;

  if (m%num_procs){
    my_start = (my_rank*m)/num_procs;
    my_stop = ((my_rank+1)*m)/num_procs;
  }
  else{
    my_start = (my_rank*m+1)/num_procs;
    my_stop = ((my_rank+2)*m)/num_procs;
  }
  if (my_rank == num_procs - 1)
    my_stop = m;

  my_m = my_stop - my_start + 1;
  my_n = n;
  int length = my_m*my_n;

  allocate_image (&u, my_m, my_n);
  allocate_image (&u_bar, my_m, my_n);


  /* each process asks process 0 for a partitioned region */
  /* of image_chars and copy the values into u */
  /* ... */

  my_image_chars = malloc(my_m*my_n*sizeof(my_image_chars));

   MPI_Gather(&length, 1, MPI_INT, &n_rows[my_rank], 1, MPI_INT, 0, MPI_COMM_WORLD);

  convert_jpeg_to_image (my_image_chars, &u);
  iso_diffusion_denoising_parallel (&u, &u_bar, kappa, iters);

  /* each process sends its resulting content of u_bar to process 0 */
  /* process 0 receives from each process incoming values and */
  /* copy them into the designated region of struct whole_image */
  /* ... */

  if (my_rank==0) {
  convert_image_to_jpeg(&whole_image, image_chars);
  export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
  deallocate_image (&whole_image);
  }

  deallocate_image (&u);
  deallocate_image (&u_bar);
  MPI_Finalize (); // end of MPI program. Want to conclude. No argument.

  return 0;
}


// mpirun -np 4 ./a.out
// here 4 stands for 4 processors