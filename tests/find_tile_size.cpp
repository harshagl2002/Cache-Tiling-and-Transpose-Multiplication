
#include "naivelinalg.h"

#include "basic.h"

#include "multiply.h"
#include "transpose.h"
#include "openmp.h"

#include "best_tile_size.h"
#ifndef BEST_TILE_SIZE
#define BEST_TILE_SIZE -1
#endif

#include <random>

#include <chrono>
#include <ctime>
#include <thread>

#include <omp.h>

#include <benchmark/benchmark.h>

#include "benchhelper.h"

#define MATRIX_BENCHMARK_SIZE 2048


static void BM_Transpose_Tiled(benchmark::State& state) {
  int N = state.range(0);
  int tile_size = state.range(1);
  if(tile_size < 1){ tile_size = N; }
  int n_warmup = 3;

	//SETUP
	matrix A, B;
	matrix_create(&A,N,N);
	matrix_create(&B,N,N);

	for(int i = 0; i < N*N; i++) {
        A.data[i] = rand() % 1000;
    }

	//warmup
	for(int i = 0;i<n_warmup;i++){
		transpose_tiled(A.data, B.data, N, tile_size);
	}


  for (auto _ : state) {
    auto start = std::chrono::high_resolution_clock::now();
	transpose_tiled(A.data, B.data, N, tile_size);
    auto end   = std::chrono::high_resolution_clock::now();

    auto elapsed_seconds =
      std::chrono::duration_cast<std::chrono::duration<double>>(
        end - start);

    state.SetIterationTime(elapsed_seconds.count());
  }
  state.SetItemsProcessed(state.iterations()*int64_t(N)*int64_t(N));

  //TEARDOWN
  matrix_destroy(&A);
  matrix_destroy(&B);

  state.counters["bits"] = 8*sizeof(matrix_data_t);
  state.counters["matrix_size"] = N;
  state.counters["tile_size"] = tile_size;
}

//NAMED_BENCHMARK is not part of Google Benchmark, see benchhelper.h
NAMED_BENCHMARK(BM_Transpose_Tiled_vary_tile, BM_Transpose_Tiled)->UseManualTime()
	->ArgNames({"matrix_size", "tile_size"})
	->RangeMultiplier(2)->Ranges({{MATRIX_BENCHMARK_SIZE, MATRIX_BENCHMARK_SIZE}, {2, 512}});

//NAMED_BENCHMARK is not part of Google Benchmark, see benchhelper.h
NAMED_BENCHMARK(BM_Transpose_Tiled_vary_size, BM_Transpose_Tiled)->UseManualTime()
	 	->ArgNames({"matrix_size", "tile_size"})
	 	->RangeMultiplier(2)->Ranges({{1<<7, 1<<13}, {BEST_TILE_SIZE, BEST_TILE_SIZE}});


BENCHMARK_MAIN();
