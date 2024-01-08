#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Entrer la taille de n : ");
    scanf("%d", &n);

    int tid = omp_get_thread_num();
    int nbth = omp_get_num_threads();
    int istart = (n / nbth) * (tid);
    int iend = (n / nbth) * (tid + 1);

    double **A = (double **)malloc(n * sizeof(double *));
    double **B = (double **)malloc(n * sizeof(double *));
    double **result = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
        B[i] = (double *)malloc(n * sizeof(double));
        result[i] = (double *)malloc(n * sizeof(double));
    }

    #pragma omp parallel for
    for (int i = istart; i < iend; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
            result[i][j] = 0.0;
        }
    }

    double start_time = omp_get_wtime();

    #pragma omp parallel for num_threads(8)
    for (int i = istart; i < iend; i++) {
        for (int j = istart; j < iend; j++) {
            for (int k = istart; k < iend; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    double end_time = omp_get_wtime();
    double time = end_time - start_time;

    printf("A*B = [");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", result[i][j]);
        }
    }
    printf("]\n");

    printf("Time: %f seconds\n", time);

    // Freeing allocated memory
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(result[i]);
    }
    free(A);
    free(B);
    free(result);

    return 0;
}
