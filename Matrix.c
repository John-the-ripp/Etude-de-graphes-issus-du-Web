#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


void generateSubmatrices(double **A, int n, int subSize, double ***submatrices) {
    // Allocate memory for the four submatrices
    for (int i = 0; i < 4; i++) {
        submatrices[i] = (double **)malloc(subSize * sizeof(double *));
        for (int j = 0; j < subSize; j++) {
            submatrices[i][j] = (double *)malloc(subSize * sizeof(double));
        }
    }

    // Generate four submatrices from matrix A
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
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = (double)(rand() % 10);
        }
    }
}

void initializeFiltre(double **filtre,int size){
    for (int i=0;i<size;i++){
        for(int j=0;j < size; j++){
            filtre[i][j] = (double)(rand() % 10);
        }
    }
}







int main() {
    int n = 8;
    int block_size = 4;
    int subSize = n / 2; 

    double **A = (double **)malloc(n * sizeof(double *));
    double **B = (double **)malloc(block_size * sizeof(double *));
    double **C = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
        C[i] = (double *)malloc(n * sizeof(double));
    }
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

    for (int k = 0; k < 4; k++) {
        printf("\nSubmatrix %d\n", k + 1);
        for (int i = 0; i < subSize; i++) {
            for (int j = 0; j < subSize; j++) {
                printf("%8.2lf ", submatrices[k][i][j]); 
            }
            printf("\n");
        }
    }



    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(C[i]);
    }
    for (int i = 0; i < block_size; i++) {
        free(B[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
