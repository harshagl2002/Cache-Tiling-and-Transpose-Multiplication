#ifndef _BENCHHELPER_H_
#define _BENCHHELPER_H_

#include <benchmark/benchmark.h>

#define NAMED_BENCHMARK(name, funcname)               \
  BENCHMARK_PRIVATE_DECLARE(name) =                         \
      (::benchmark::internal::RegisterBenchmarkInternal( \
new ::benchmark::internal::FunctionBenchmark(#name, funcname)))

#endif /* _BENCHHELPER_H_ */
