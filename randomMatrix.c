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


matrix* matrixAddition(matrix* m1, matrix* m2, matrix* m3, int t) {
	for (int i = 0; i < m1->matrix_size; i++) {
		for (int j = 0; j < m1->matrix_size; j++) {
			m3->matrix_array[m3->row_1 + i][m3->col_1 + j] = m1->matrix_array[m1->row_1 + i][m1->col_1 + j] + t * m2->matrix_array[m2->row_1 + i][m1->col_1 + j];
		}
	}

	return m3;
}

void standard(matrix* m1, matrix* m2, matrix* m3) {

	for (int i = 0; i < m1->matrix_size; i++) {
		for (int j = 0; j < m2->matrix_size; j++) {
			for (int k = 0; k < m2->matrix_size; k++) {
				
				m3->matrix_array[m3->row_1 + i][m3->col_1 + k] = m3->matrix_array[m3->row_1 + i][m3->col_1 + k] + m1->matrix_array[m1->row_1 + i][m1->col_1 + j] * m2->matrix_array[m2->row_1 + j][m2->col_1 + k];

			}
		}
	}
}

matrix* createMatrix(int n) {
	matrix* n_matrix = malloc(sizeof(matrix));
	n_matrix->matrix_size = n;
	n_matrix->matrix_array = malloc(sizeof(int*) * n);
	n_matrix->col_1 = 0;
	n_matrix->row_1 = 0;
	for (int i = 0; i < n; i++) {
		n_matrix->matrix_array[i] = calloc(n, sizeof(int));
	}
	return n_matrix;
}



void modifiedStrassens(matrix* m3, matrix* m1, matrix* m2, int N) {

	if (m1->matrix_size <= N || m1->matrix_size <= N || m2->matrix_size <= N) {
		standard(m1, m2, m3);
		return;
	}
	
	matrix* matrices1[4];
	matrix* matrices2[4];
	quadrantMatrices(matrices1, m1);
	quadrantMatrices(matrices2, m2);

	matrix* pt[8];
	for (int i = 1; i < 8; i++) {
		pt[i] = createMatrix(m3->matrix_size / 2);
	}
	matrix* tmp1 = createMatrix(m3->matrix_size / 2);
	matrix* tmp2 = createMatrix(m3->matrix_size / 2);

	modifiedStrassens(pt[1], matrices1[0], matrixAddition(tmp1, matrices2[1], matrices2[3], -1), N);
	modifiedStrassens(pt[2], matrixAddition(tmp1, matrices1[0], matrices1[1], 1), matrices2[3], N);
	modifiedStrassens(pt[3], matrixAddition(tmp1, matrices1[2], matrices1[3], 1), matrices2[0], N);
	modifiedStrassens(pt[4], matrices1[3], matrixAddition(tmp1, matrices2[2], matrices2[0], -1), N);
	modifiedStrassens(pt[5], matrixAddition(tmp1, matrices1[0], matrices1[3], 1), matrixAddition(tmp2, matrices2[0], matrices2[3], 1), N);
	modifiedStrassens(pt[6], matrixAddition(tmp1, matrices1[1], matrices1[3], -1), matrixAddition(tmp2, matrices2[2], matrices2[3], 1), N);
	modifiedStrassens(pt[7], matrixAddition(tmp1, matrices1[0], matrices1[2], -1), matrixAddition(tmp2, matrices2[0], matrices2[1], 1), N);

	m3->matrix_size = m3->matrix_size / 2;
	matrixAddition(m3, pt[5], matrixAddition(tmp1, pt[4], matrixAddition(tmp2, pt[6], pt[2], -1), 1), 1);
	m3->col_1 = m3->matrix_size;
	matrixAddition(m3, pt[1], pt[2], 1);
	m3->row_1 = m3->matrix_size;
	matrixAddition(m3, pt[5], matrixAddition(tmp1, pt[1], matrixAddition(tmp2, pt[3], pt[7], 1), -1), 1);
	m3->col_1 = 0;
	matrixAddition(m3, pt[3], pt[4], 1);
	m3->row_1 = 0;
	m3->matrix_size = m3->matrix_size * 2;

	freeMatrix(tmp1);
	freeMatrix(tmp2);
	for (int i = 1; i < 8; i++) {
		freeMatrix(pt[i]);
	}
	freeQuadrants(matrices1);
	freeQuadrants(matrices2);
}