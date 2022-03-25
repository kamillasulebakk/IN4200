#include <stdlib.h> // malloc and free.
#include <stdio.h>  // printf
#include <math.h>

int zeros2D(double ***A, int n, int m)
{
    *A = malloc(n * sizeof *A);
    (*A)[0] = malloc(n*m * sizeof (*A)[0]);
    if (!(*A)[0] || !*A){
        // Allocation failed.
        printf("Allocation failed\n");
        return 1;
    }

    for (size_t i = 1; i < n; i++)
        (*A)[i] = &((*A)[0][i*m]);
    for (size_t i = 0; i < n*m; i++)
      (*A)[0][i] = 0.0;
    return 0;
}

// Free pointers allocated in alloc2D.
int free2D(double **A)
{
    free(A[0]);
    free(A);
    return 0;
}

// Print matrix values.
int printmat(double **A, int n, int m)
{
    for (size_t i = 0; i < n; ++i){
        printf("| ");
        for (size_t j = 0; j < m; ++j){
            printf("%6.2lf ", A[i][j]);
        }
        printf("|\n");
    }
    return 0;
}


int printvec_d(double *y, int N)
{
    printf("(");
    for (size_t i = 0; i < N-1; i++) {
        printf("%lf, ", y[i]);
    }
    printf("%lf", y[N-1]);
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

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}


// Function to perform Selection Sort
void sort_inplace(int *a, int *b, size_t n)
{
  size_t i, j, min_idx;

  // One by one move boundary of unsorted subarray
  for (i = 0; i < n - 1; i++) {
    // Find the minimum element in unsorted array
    min_idx = i;
    for (j = i + 1; j < n; j++)
      if (a[j] < a[min_idx])
        min_idx = j;

    // Swap the found minimum element
    // with the first element
    swap(&(a[min_idx]), &(a[i]));
    swap(&(b[min_idx]), &(b[i]));

  }
  
}

void sort(int *arr, int start, int stop){
    if (start > stop + 1){
        int piv = arr[start], l = start + 1, r = stop;
        while (l < r){
            if (arr[l] <= piv)
                l++;
        else
            swap(&arr[l], &arr[--r]);
        }
    swap(&arr[--l], &arr[start]);
    sort(arr, start, l);
    sort(arr, r, stop);
    }
}