#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


typedef struct matrix {
	int col_1;
 	int row_1;
	int** matrix_array;
	int matrix_size;
} matrix;

matrix* randomMatrix(int n) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand((unsigned) tv.tv_usec);
	matrix* n_matrix = malloc(sizeof(matrix));
	n_matrix->col_1 = 0;
	n_matrix->row_1 = 0;
	n_matrix->matrix_size = n;
	n_matrix->matrix_array = malloc(sizeof(int*) * n);

	for (int i = 0; i < n; i++) {
		n_matrix->matrix_array[i] = calloc(n, sizeof(int));
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int cell_val = rand() % 3 - 1;
			n_matrix->matrix_array[n_matrix->row_1 + i][n_matrix->col_1 + j] = cell_val;
		}
	}
	return n_matrix;
}

void freeMatrix(matrix* n_matrix) {
	for (int i = 0; i < n_matrix->matrix_size; i++) {
		free(n_matrix->matrix_array[i]);
	}
	free(n_matrix->matrix_array);
	free(n_matrix);
}


void quadrantMatrices(matrix** matrices, matrix* n_matrix) {
	for (int i = 0; i < 4; i++) {
		matrices[i] = malloc(sizeof(matrix));
		matrices[i]->matrix_array = n_matrix->matrix_array;
		matrices[i]->matrix_size = n_matrix->matrix_size / 2;
		if (i / 2 == 0) {
			matrices[i]->row_1 = n_matrix->row_1;
		} else {
			matrices[i]->row_1 = n_matrix->row_1 + n_matrix->matrix_size / 2;
		}
		if (i % 2 == 0) {
			matrices[i]->col_1 = n_matrix->col_1;
		} else {
			matrices[i]->col_1 = n_matrix->col_1 + n_matrix->matrix_size / 2;
		}
	}
}

void freeQuadrants(matrix** matrices) {
	for (int i = 0; i < 4; i++) {
		free(matrices[i]);
	}
}