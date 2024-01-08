#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void generateSubmatrices(double **A, int n, int subSize, double ***submatrices) {
    for (int i = 0; i < 4; i++) {
        submatrices[i] = (double **)malloc(subSize * sizeof(double *));
        for (int j = 0; j < subSize; j++) {
            submatrices[i][j] = (double *)malloc(subSize * sizeof(double));
        }
    }

    for (int i = 0; i < subSize; i++) {
        for (int j = 0; j < subSize; j++) {
            submatrices[0][i][j] = A[i][j];
            submatrices[1][i][j] = A[i][j + subSize];
            submatrices[2][i][j] = A[i + subSize][j];
            submatrices[3][i][j] = A[i + subSize][j + subSize];
        }
    }
}

void initializeMatrix(double **matrix, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        matrix[i] = (double *)malloc(size * sizeof(double));
        for (int j = 0; j < size; j++) {
            matrix[i][j] = (double)(rand() % 10);
        }
    }
}

void initializeFilter(double **filter, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        filter[i] = (double *)malloc(size * sizeof(double));
        for (int j = 0; j < size; j++) {
            filter[i][j] = (double)(rand() % 10);
        }
    }
}

double multiplyAndSum(double **submatrix, double **filter, int size) {
    double result = 0.0;
    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result += submatrix[i][j] * filter[i][j];
        }
    }
    return result;
}

int main() {
    int n;
    printf("Enter the size of the Main matrix: ");
    scanf("%d", &n);

    int subSize = n / 2;
    int block_size = n / 2;

    double **A = (double **)malloc(n * sizeof(double *));
    double **B = (double **)malloc(block_size * sizeof(double *));
    double *C = (double *)malloc(4 * sizeof(double));

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
    }

    #pragma omp parallel for
    for (int i = 0; i < block_size; i++) {
        B[i] = (double *)malloc(block_size * sizeof(double));
    }

    initializeMatrix(A, n);
    initializeMatrix(B, block_size);

    printf("MATRICE A\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2lf ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nMATRICE B (Filter)\n");
    for (int i = 0; i < block_size; i++) {
        for (int j = 0; j < block_size; j++) {
            printf("%8.2lf ", B[i][j]);
        }
        printf("\n");
    }

    double ***submatrices = (double ***)malloc(4 * sizeof(double **));
    generateSubmatrices(A, n, subSize, submatrices);

    double start = omp_get_wtime();

    #pragma omp parallel for 
    for (int k = 0; k < 4; k++) {
        C[k] = multiplyAndSum(submatrices[k], B, subSize);
    }   

    double end = omp_get_wtime();
    double execution_time = end - start;

    printf("\nArray C (Result)\n");
    for (int i = 0; i < 4; i++) {
        printf("%8.2lf ", C[i]);
    }
    printf("\n");

    printf("TIME of EXECUTION IS: %lf seconds\n", execution_time);

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }

    #pragma omp parallel for
    for (int i = 0; i < block_size; i++) {
        free(B[i]);
    }

    free(A);
    free(B);
    free(C);

    return 0;
}
