
#include <random>

#include "naivelinalg.h"

#include "best_tile_size.h"

#ifndef BEST_TILE_SIZE
#define BEST_TILE_SIZE -1
#endif

#include "multiply.h"
#include "transpose.h"
#include "openmp.h"

#include "gtest/gtest.h"


TEST(Transpose, TiledCorrect) {
    int n = 8;
    int tile_size = 4;

	std::default_random_engine generator;
	std::normal_distribution<double> distribution(5.0,25.0);

	matrix A, B_basic, B_tiled;
	matrix_create(&A,n,n);
	matrix_create(&B_basic,n,n);
	matrix_create(&B_tiled,n,n);

    for (int i = 0; i < n*n; i++) {
        A.data[i] = distribution(generator);
    }

    matrix_transpose(&B_basic, &A);
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
    EXPECT_EQ(true,is_same);
}

TEST(Cache, TileSizeChosen){
	EXPECT_NE(-1,BEST_TILE_SIZE) << "You have not chosen a best tile size in transpose/best_tile_size.h";

	// At grading time, your tile size will be compared to the known answer.
	// But that's hidden from you now.

    //TODO: Determine if the chosen BEST_TILE_SIZE is a power of 2 or not.
}




TEST(Multiply, TiledCorrect) {
	int n = 8;
	int tile_size = 4;

	std::default_random_engine generator;
	std::normal_distribution<double> distribution(5.0,25.0);

	matrix A, B, C_basic, C_tiled;
	matrix_create(&A,n,n);
	matrix_create(&B,n,n);
	matrix_create(&C_basic,n,n);
	matrix_create(&C_tiled,n,n);

    for (int i = 0; i < n*n; i++) {
        A.data[i] = distribution(generator);
        B.data[i] = distribution(generator);
        C_basic.data[i] = distribution(generator);//Students should not expect pre-zeroed output.
        C_tiled.data[i] = distribution(generator);//Students should not expect pre-zeroed output.
    }


    //multiply_basic(A.data, B.data, C_basic.data, n);
	matrix_mult_naive(&C_basic, &A, &B);
    multiply_tiled(A.data, B.data, C_tiled.data, n, tile_size);

    EXPECT_TRUE( matrix_equality(&C_basic, &C_tiled, 0.00001) ) << "Matrices not identical.";

    cout << "Expected ans" << endl;


	matrix_destroy(&A);
	matrix_destroy(&B);
	matrix_destroy(&C_basic);
	matrix_destroy(&C_tiled);

}


TEST(Multiply, TransposedCorrect) {
    int n = 8;
    int tile_size = 4;
    /*
	double *A = (double*)malloc(n*n*sizeof(double));
    double *B = (double*)malloc(n*n*sizeof(double));
    double *C_basic = (double*)malloc(n*n*sizeof(double));
    double *C_transposed = (double*)malloc(n*n*sizeof(double));
	*/
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(5.0,25.0);

	matrix A, B, C_basic, C_tiled,C_transposed;
	matrix_create(&A,n,n);
	matrix_create(&B,n,n);
	matrix_create(&C_basic,n,n);
	matrix_create(&C_transposed,n,n);

    for (int i = 0; i < n*n; i++) {
        A.data[i] = distribution(generator);
        B.data[i] = distribution(generator);
        C_basic.data[i] = distribution(generator);
        C_transposed.data[i] = distribution(generator);
    }

	matrix B_T;
	matrix_create(&B_T,n,n);
    matrix_transpose(&B_T, &B);

    matrix_mult_naive(&C_basic, &A, &B);
    multiply_transposed(A.data, B_T.data, C_transposed.data, n);

    EXPECT_TRUE( matrix_equality(&C_basic, &C_transposed, 0.00000001) ) << "Matrices not identical.";

	matrix_destroy(&A);
	matrix_destroy(&B);
	matrix_destroy(&B_T);
	matrix_destroy(&C_basic);
	matrix_destroy(&C_transposed);
}


void squares_serial(double* A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = pow(A[i], 2);
    }
}

void primes_serial(bool* A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = prime_test(i+2);
    }
}

TEST(OpenMP, SquaresCorrect) {
    int n = 16;
    double* A = (double*)malloc(n*sizeof(double));
    double* A2 = (double*)malloc(n*sizeof(double));

    /*
    //Not needed for tests of correctness. Probably needed for benchmarks.
	int memalign_result = posix_memalign(
						(void**)(&A),
	 					64,
						n*sizeof(double)
					);
	memalign_result = posix_memalign(
						(void**)(&A2),
					 	64,
						n*sizeof(double)
					);
    */

    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
        A2[i] = A[i];
    }

    squares_serial(A, n);
    squares_parallel(A2, n);

    for (int i = 0; i < n; i++) {
        if (abs(A[i] - A2[i]) > 0.000001){
            ADD_FAILURE(); break; //So that we can free dynamic memory.
        }
    }
    
    free(A);
    free(A2);
}

TEST(OpenMP, PrimesCorrect) {
    int n = 16;
    bool* A = (bool*)malloc(n*sizeof(bool));
    bool* A2 = (bool*)malloc(n*sizeof(bool));

    primes_serial(A, n);
    primes_parallel(A2, n);

    for (int i = 0; i < n; i++) {
        if (A[i] != A2[i]){
            ADD_FAILURE(); break; //So that we can free dynamic memory.
        }
    }
    
    free(A);
    free(A2);
}
