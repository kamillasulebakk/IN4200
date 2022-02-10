#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Return random double in range [min, max].
double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

int main(int argc, char const *argv[]) {
    // if (argc < 2) {
    //     printf("Usage: ./prog.exe N_ELEMENTS\n");
    //     return 1;
    // }
    // int N = atoi(argv[2]);

    int N = 10;

    double *A = malloc(N * sizeof *A);
    double *B = malloc(N * sizeof *B);

    // Assigning some random numbers:
    srand(time(NULL)); // Seeds the random number generator.

    for (size_t i = 0; i < N; i++) {
        A[i] = randfrom(0., 2.); // This function is from our header.
        B[i] = randfrom(0., 2.);
    }

    double s = 1.5;

    clock_t start = clock();
    for (size_t i = 0; i < N; i++) {
        A[i] = s*B[i];
    }
    clock_t end = clock();

    double total = (double)(end - start)/CLOCKS_PER_SEC;
    int n_bytes = 2 * N * sizeof *A; // Guess we multiply with two as we have two arrays

    printf("Time: %lfms\n", 1000*total);
    printf("Bytes per sec: %3e\n", n_bytes/total); // This is the memory bandwith of the CPU
    printf("Flops: %3e\n", N/total);

    free(A);
    free(B);

    return 0;
}

