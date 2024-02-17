#include "transpose.h"
#include "basic.h"
#include "util.h"

#include <random>
#include <cassert>

#include "naivelinalg.h"

bool transposeTiledIsCorrect() {
    int n = 8;
    int tile_size = 4;

	matrix A, B_basic, B_tiled;
	matrix_create(&A,n,n);
	matrix_create(&B_basic,n,n);
	matrix_create(&B_tiled,n,n);

    for (int i = 0; i < n*n; i++) {
        A.data[i] = rand() % 100;
    }

    transpose_basic(A.data, B_basic.data, n);
    transpose_tiled(A.data, B_tiled.data, n, tile_size);

    bool is_same = matrix_equality(&B_basic,&B_tiled,0.0);

	if(!is_same){
		matrix_fprint(stderr, &A);
		fprintf(stderr,"\n\n");
		matrix_fprint(stderr, &B_tiled);
	}

    matrix_destroy(&A);
    matrix_destroy(&B_basic);
    matrix_destroy(&B_tiled);
    return is_same;
}

double timeTransposeBasic(double* A, double* B, int N) {
    clear_cache();

    double start = get_time();
    transpose_basic(A, B, N);
    return get_time() - start;
}

double timeTransposeTiled(double* A, double* B, int N, int tile_size) {
    clear_cache();

    double start = get_time();
    transpose_tiled(A, B, N, tile_size);
    return get_time() - start;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: ./transpose_runner array_size tile_size [num_trials]\n");
        return 0;
    }
    int num_trials = 1;
    int N = atoi(argv[1]);
    int tile_size = atoi(argv[2]);
    if (argc > 3) num_trials = atoi(argv[3]);

	matrix A, B;
	matrix_create(&A,N,N);
	matrix_create(&B,N,N);

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            A.data[i*N + j] = rand() % 1000;

    double total_elapsed = 0.0;
    for (int t = 0; t < num_trials; t++) {
        total_elapsed += timeTransposeBasic(A.data, B.data, N);
    }
    printf("Average execution time of transpose_basic(): %f\n", total_elapsed/num_trials);

    assert(transposeTiledIsCorrect());

    total_elapsed = 0.0;
    for (int t = 0; t < num_trials; t++) {
        total_elapsed += timeTransposeTiled(A.data, B.data, N, tile_size);
    }
    printf("Average execution time of transpose_tiled(): %f\n", total_elapsed/num_trials);

    matrix_destroy(&A);
	matrix_destroy(&B);
    return 0;
}
