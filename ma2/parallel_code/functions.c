#include "../serial_code/functions.h"
#include "utils.h"

void send_and_receive_overlap(image *u){
  int my_rank, num_procs;

  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

  const bool i_am_even = (my_rank % 2 == 0);

  if (i_am_even){
    if (overlap_below(my_rank, num_procs)){
      MPI_Recv(u->image_data[m-1], n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD);
      MPI_Send(u->image_data[m-2], n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD);
    }
    if (overlap_above(my_rank)){
      MPI_Send(u->image_data[1], n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD);
      MPI_Recv(u->image_data[0], n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD);
    }
  } else {
    MPI_Send(u->image_data[1], n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD);
    MPI_Recv(u->image_data[0], n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD);
    if (overlap_below(my_rank, num_procs)){
      MPI_Recv(u->image_data[m-1], n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD);
      MPI_Send(u->image_data[m-2], n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD);
    }
  }
}

void iso_diffusion_denoising_parallel(
  image *u, image *u_bar, float kappa, const int iters)
{
  const int m = u->m;
  const int n = u->n;

  for (size_t i = 0; i < iters; i++){
    iso_diffusion_denoising(u, u_bar, kappa, 1);
    send_and_receive_overlap(u_bar);
    swap(u, u_bar);
  }
  if (iters % 2 == 1)
    swap(u, u_bar);
}
