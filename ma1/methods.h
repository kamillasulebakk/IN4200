#ifndef METHODS_H
#define METHODS_H

#include <stdlib.h> // malloc and free.
#include <stdio.h>  // printf

// int zeros2D(double ***A, int n, int m);
int printvec_d(double *y, int N);
int printvec_i(int *y, int N);
void swap_i(int* xp, int* yp);
void swap_d(double* xp, double* yp);
void sort_inplace(int *arr, int start, int stop);

#endif
