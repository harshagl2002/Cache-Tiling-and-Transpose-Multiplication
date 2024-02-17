#include "multiply.h"
#include "util.h"
#include "basic.h"

#include <random>
#include <cassert>
#include <cmath>

#include "naivelinalg.h"

bool multiplyTiledIsCorrect() {
    int n = 8;
    int tile_size = 4;

	matrix A, B, C_basic, C_tiled;
	matrix_create(&A,n,n);
	matrix_create(&B,n,n);
	matrix_create(&C_basic,n,n);
	matrix_create(&C_tiled,n,n);

    for (int i = 0; i < n*n; i++) {
        A.data[i] = rand() % 100;
        B.data[i] = rand() % 100;
        C_basic.data[i] = 0.0;
        C_tiled.data[i] = 0.0;
    }

    multiply_basic(A.data, B.data, C_basic.data, n);
    multiply_tiled(A.data, B.data, C_tiled.data, n, tile_size);

    bool is_same = matrix_equality(&C_basic, &C_tiled, 0.00001);

	matrix_destroy(&A);
	matrix_destroy(&B);
	matrix_destroy(&C_basic);
	matrix_destroy(&C_tiled);
    return is_same;
}

bool multiplyTransposedIsCorrect() {
    int n = 8;
    int tile_size = 4;
    /*
	double *A = (double*)malloc(n*n*sizeof(double));
    double *B = (double*)malloc(n*n*sizeof(double));
    double *C_basic = (double*)malloc(n*n*sizeof(double));
    double *C_transposed = (double*)malloc(n*n*sizeof(double));
	*/

	matrix A, B, C_basic, C_tiled,C_transposed;
	matrix_create(&A,n,n);
	matrix_create(&B,n,n);
	matrix_create(&C_basic,n,n);
	matrix_create(&C_transposed,n,n);

    for (int i = 0; i < n*n; i++) {
        A.data[i] = rand() % 100;
        B.data[i] = rand() % 100;
        C_basic.data[i] = 0.0;
        C_transposed.data[i] = 0.0;
    }

	matrix B_T;
	matrix_create(&B_T,n,n);
    transpose_basic(B.data, B_T.data, n);

    multiply_basic(A.data, B.data, C_basic.data, n);
    multiply_transposed(A.data, B_T.data, C_transposed.data, n);

    bool is_same = matrix_equality(&C_basic, &C_transposed, 0.00000001);

	/*
    free(A);
    free(B);
    free(B_T);
    free(C_basic);
    free(C_transposed);
	*/
	matrix_destroy(&A);
	matrix_destroy(&B);
	matrix_destroy(&B_T);
	matrix_destroy(&C_basic);
	matrix_destroy(&C_transposed);
    return is_same;
}

double timeMultiplyTiled(double* A, double* B, double* C, int N, int tile_size) {
    clear_cache();

    double start = get_time();
    multiply_tiled(A, B, C, N, tile_size);
    return get_time() - start;
}

double timeMultiplyTransposed(double* A, double* B_T, double* C, int N) {
    clear_cache();

    double start = get_time();
    multiply_transposed(A, B_T, C, N);
    return get_time() - start;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: ./multiply_runner array_size tile_size [num_trials]\n");
        return 0;
    }
    int num_trials = 1;
    int N = atoi(argv[1]);
    int tile_size = atoi(argv[2]);
    if (argc > 3) num_trials = atoi(argv[3]);

	matrix A, B, C, B_T;
	matrix_create(&A,N,N);
	matrix_create(&B,N,N);
	matrix_create(&C,N,N);
	matrix_create(&B_T,N,N);

    for(int i = 0; i < N*N; i++) {
        A.data[i] = rand() % 1000;
        B.data[i] = rand() % 1000;
    }

    // Check that multiply_basic and multiply_tiled do the same computation
    assert(multiplyTiledIsCorrect());

    double total_elapsed = 0.0;
    for (int t = 0; t < num_trials; t++) {
        clear_cache();

        double start = get_time();
        multiply_basic(A.data, B.data, C.data, N);
        total_elapsed += get_time() - start;
    }
    printf("Average execution time of multiply_basic(): %f\n", total_elapsed/num_trials);

    total_elapsed = 0.0;
    for (int t = 0; t < num_trials; t++) {
        total_elapsed += timeMultiplyTiled(A.data, B.data, C.data, N, tile_size);
    }
    printf("Average execution time of multiply_tiled(): %f\n", total_elapsed/num_trials);

    transpose_basic(B.data, B_T.data, N);

    // Check that multiply_basic and multiply_transposed do the same computation
    assert(multiplyTransposedIsCorrect());

    total_elapsed = 0.0;
    for (int t = 0; t < num_trials; t++) {
        total_elapsed += timeMultiplyTransposed(A.data, B_T.data, C.data, N);
    }
    printf("Average execution time of multiply_transposed(): %f\n", total_elapsed/num_trials);

    matrix_destroy(&A);
    matrix_destroy(&B);
    matrix_destroy(&B_T);
    matrix_destroy(&C);
    return 0;
}
