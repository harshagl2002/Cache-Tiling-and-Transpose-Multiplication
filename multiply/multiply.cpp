#include "multiply.h"
#include "util.h"


void multiply_tiled(double* const A, double* const B, double* const C, int const N, const int tile_size) {
	/* The file `multiply.h` contains Doxygen headers that explain
		all parameters and expectations of this function.
		Read it.
	*/

	/* HINT: It may be much easier to add one or two inline helper functions
		to this .cpp file to handle single blocks.
		This lets you separate the logic, making it much easier to debug.
	*/

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			C[i * N + j] = 0.0;
		}
	}


	for (int ii = 0; ii < N; ii += tile_size) {
		for (int jj = 0; jj < N; jj += tile_size) {
			for (int kk = 0; kk < N; kk += tile_size) {
				for (int i = ii; i < min(N, ii + tile_size); i++) {
					for (int j = jj; j < min(N, jj + tile_size); j++) {
						register double tmpval = 0.0; // Initialize tmpval inside the innermost loop
						for (int k = kk; k < min(N, kk + tile_size); k++) {
							tmpval += A[IND(i,k,N)] * B[IND(k,j,N)]; // Accumulate the products
						}
						C[IND(i,j,N)] += tmpval; // Store the final result in C
					}
				}
			}
		}
	}
}


void multiply_transposed(double* const A, double* const B_T, double* const C, const int N) {
    // Transpose matrix B
    double B[N * N];
    transpose_basic(B_T, B, N);
	multiply_tiled(A, B, C, N, 8);

}

