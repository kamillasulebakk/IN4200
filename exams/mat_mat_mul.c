#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	double **A, **B, **C;
	int n, m, p;

	n = 500;
	m = 473;
	p = 612;

	A = malloc(sizeof(double*)*n);
	B = malloc(sizeof(double*)*m);
	C = malloc(sizeof(double*)*n);

	for (int i = 0; i < n; i++) {
		A[i] = malloc(sizeof(double)*m);
		C[i] = malloc(sizeof(double)*p);
	
	    for (int j = 0; j < m; j++) {
	    	A[i][j] = 0.1*i*j;
	    }
	    for (int j = 0; j < p; j++) {
	    	C[i][j] = 0;
	    }
	}
	for (int i = 0; i < m; i++) {
		B[i] = malloc(sizeof(double)*p);
		for (int j = 0; j < p; j++) {
			B[i][j] = -0.1*i*j;
		}
	}

	double time = omp_get_wtime();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j++) {
			for (int k = 0; k < m; k++) {
				C[i][j] = A[i][k]*B[k][j];
			}
		}
	}
	time = omp_get_wtime() - time;

	printf("Normal: %fs\n", time);

	time = omp_get_wtime();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j+=4) {
			for (int k = 0; k < m; k++) {
				C[i][j] = A[i][k]*B[k][j];
				C[i][j+1] = A[i][k]*B[k][j+1];
				C[i][j+2] = A[i][k]*B[k][j+2];
				C[i][j+3] = A[i][k]*B[k][j+3];
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = p - p%4; j < p; j++) {
			for (int k = 0; k < m; k++) {
				C[i][j] = A[i][k]*B[k][j];
			}
		}
	}
	time = omp_get_wtime() - time;

	printf("Unroll j: %fs\n", time);

    time = omp_get_wtime();
	for (int i = 0; i < n; i+=4) {
		for (int j = 0; j < p; j++) {
			for (int k = 0; k < m; k++) {
				C[i][j] = A[i][k]*B[k][j];
				C[i+1][j] = A[i+1][k]*B[k][j];
				C[i+2][j] = A[i+2][k]*B[k][j];
				C[i+3][j] = A[i+3][k]*B[k][j];
			}
		}
	}
	for (int i = n - n%4; i < n; i++) {
		for (int j = 0; j < p; j++) {
			for (int k = 0; k < m; k++) {
				C[i][j] = A[i][k]*B[k][j];
			}
		}
	}
    time = omp_get_wtime() - time;

	printf("Unroll i: %fs\n", time);
	return 0;
}