#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


typedef struct matrix {
	int col_1;
 	int row_1;
	int** matrix_array;
	int matrix_size;
} matrix;


matrix* generateMatrix(int n) {
	matrix* n_matrix = malloc(sizeof(matrix));
	n_matrix->col_1 = 0;
	n_matrix->row_1 = 0;
	n_matrix->matrix_size = n;
	n_matrix->matrix_array = malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++) {
		n_matrix->matrix_array[i] = calloc(n, sizeof(int));
	}
	return n_matrix;
}

void cellVal(matrix* n_matrix, int i, int j, int value) {
	n_matrix->matrix_array[n_matrix->row_1 + i][n_matrix->col_1 + j] = value;
}


matrix* randomMatrix(int n) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand((unsigned) tv.tv_usec);
	matrix* n_matrix = generateMatrix(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int e = rand() % 3 - 1;
			cellVal(n_matrix, i, j, e);
		}
	}
	return n_matrix;
}