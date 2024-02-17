#include "util.h"


#include "transpose.h"

void transpose_tiled(double* A, double* B, int N, int tile_size) {
	/* The file `transpose.h` contains Doxygen headers that explain
		all parameters and expectations of this function.
		Read it.
	*/

	for (int i = 0; i < N; i += tile_size) {
        for (int j = 0; j < N; j += tile_size) {
            // Transpose each tile
            for (int ii = i; ii < min(N, i + tile_size); ++ii) {
                for (int jj = j; jj < min(N, j + tile_size); ++jj) {
                    B[ii * N + jj] = A[jj * N + ii];
                }
            }
        }
    }
}
