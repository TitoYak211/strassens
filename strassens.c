#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

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
	n_matrix->matrix_size = n;
	n_matrix->matrix_array = malloc(sizeof(int*) * n);
	n_matrix->col_1 = 0;
	n_matrix->row_1 = 0;

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

void modifiedStrassens(matrix* m1, matrix* m2, matrix* m3, int N) {
	if (m1->matrix_size <= N || m2->matrix_size <= N) {
		standard(m1, m2, m3);
		return;
	}
	
	matrix* matrix_m1[4];
	quadrantMatrices(matrix_m1, m1);

	matrix* matrix_m2[4];
	quadrantMatrices(matrix_m2, m2);

	matrix* m[8];
	for (int i = 1; i < 8; i++) {
		m[i] = createMatrix(m3->matrix_size / 2);
	}

	matrix* t1 = createMatrix(m3->matrix_size / 2);
	matrix* t2 = createMatrix(m3->matrix_size / 2);

	modifiedStrassens(m[1], matrix_m1[0], matrixAddition(t1, matrix_m2[1], matrix_m2[3], -1), N);
	modifiedStrassens(m[2], matrixAddition(t1, matrix_m1[0], matrix_m1[1], 1), matrix_m2[3], N);
	modifiedStrassens(m[3], matrixAddition(t1, matrix_m1[2], matrix_m1[3], 1), matrix_m2[0], N);
	modifiedStrassens(m[4], matrix_m1[3], matrixAddition(t1, matrix_m2[2], matrix_m2[0], -1), N);
	modifiedStrassens(m[5], matrixAddition(t1, matrix_m1[0], matrix_m1[3], 1), matrixAddition(t2, matrix_m2[0], matrix_m2[3], 1), N);
	modifiedStrassens(m[6], matrixAddition(t1, matrix_m1[1], matrix_m1[3], -1), matrixAddition(t2, matrix_m2[2], matrix_m2[3], 1), N);
	modifiedStrassens(m[7], matrixAddition(t1, matrix_m1[0], matrix_m1[2], -1), matrixAddition(t2, matrix_m2[0], matrix_m2[1], 1), N);

	m3->matrix_size = m3->matrix_size / 2;
	matrixAddition(m3, m[5], matrixAddition(t1, m[4], matrixAddition(t2, m[6], m[2], -1), 1), 1);
	m3->col_1 = m3->matrix_size;
	matrixAddition(m3, m[1], m[2], 1);
	m3->row_1 = m3->matrix_size;
	matrixAddition(m3, m[5], matrixAddition(t1, m[1], matrixAddition(t2, m[3], m[7], 1), -1), 1);
	m3->col_1 = 0;
	matrixAddition(m3, m[3], m[4], 1);
	m3->row_1 = 0;
	m3->matrix_size = m3->matrix_size * 2;

	freeMatrix(t1);
	freeMatrix(t2);
	
	for (int i = 1; i < 8; i++) {
		freeMatrix(m[i]);
	}

	freeQuadrants(matrix_m1);
	freeQuadrants(matrix_m2);
}


int runProg(int crossover, int d, int flag, char* filename) {
	matrix* n_matrix[2];
	n_matrix[0] = createMatrix(d);
	n_matrix[1] = createMatrix(d);

	FILE* f = fopen(filename, "r");

	char x[11];

	for (int i = 0, n = d * d; i < 2 * n; i++) {
		fscanf(f, "%s\n", x);
		n_matrix[i / n]->matrix_array[n_matrix[i / n]->row_1 + (i % n) / d][n_matrix[i / n]->col_1 + i % d] = (int) strtol(x, NULL, 10);
	}

	fclose(f);

	matrix* x_matrix = createMatrix(d);

	time_t s = time(NULL);

	modifiedStrassens(x_matrix, n_matrix[0], n_matrix[1], crossover);

	time_t e = time(NULL);

	if (flag == 0) {
		for (int i = 0; i < d; i++) {
			printf("%i\n", x_matrix->matrix_array[x_matrix->row_1 + i][x_matrix->col_1 + i]);
		}
		printf("\n");
	} else {
		printf("Run time for %i, dim %i: %ld\n", crossover, d, e - s);
	}

	freeMatrix(x_matrix);
	freeMatrix(n_matrix[0]);
	freeMatrix(n_matrix[1]);

	return e - s;
}


int main(int argc, char* argv[]) {
	int crossover = 75;

	int matrix_dimension = (int) strtol(argv[2], NULL, 10);
	int flag = (int) strtol(argv[1], NULL, 10);

	runProg(crossover, matrix_dimension, flag, argv[3]);

	
	return 0;
}
