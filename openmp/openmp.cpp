#include "openmp.h"
#include "util.h"
#include <omp.h>
#include <cmath>

void squares_parallel(double* A, int n) {
    // TODO: insert OpenMP pragma statement
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        A[i] = pow(A[i], 2);
    }
}


void primes_parallel(bool* A, int n) {
    // TODO: insert OpenMP pragma statement
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        A[i] = prime_test(i+2);
    }
}
