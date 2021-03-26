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

