#include <mpi.h>
#include <stdio.h>

int main(int nargs, char** args) {
    int my_rank;
    int num_procs;

    MPI_Init(&nargs, &args);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    printf("Hello world, I have rank %d out of %d procs.\n", my_rank, num_procs);
    MPI_Finalize();
    
}