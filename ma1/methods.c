#include "methods.h"

int printvec_d(double *y, int N)
{
    printf("(");
    for (size_t i = 0; i < N-1; i++) {
        printf("%8.6lf, ", y[i]);
    }
    printf("%8.6lf", y[N-1]);
    printf(")\n");
    return 0;
}

int printvec_i(int *y, int N)
{
    printf("(");
    for (size_t i = 0; i < N-1; i++) {
        printf("%4d, ", y[i]);
    }
    printf("%4d", y[N-1]);
    printf(")\n");
    return 0;
}

void swap_i(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void swap_d(double* xp, double* yp)
{
    double temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort_inplace(int *arr, int start, int stop){
    if (start > stop + 1){
        int pivotValue = arr[start], left = start + 1, right = stop;
        while (left < right){
            if (arr[left] <= pivotValue)
                left++;
        else
            swap_i(&arr[left], &arr[--right]);
        }
    swap_i(&arr[--left], &arr[start]);
    sort_inplace(arr, start, left);
    sort_inplace(arr, right, stop);
    }
}

