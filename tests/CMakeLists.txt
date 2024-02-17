cmake_minimum_required (VERSION 3.5)
project(mp1-tests VERSION 1.0.0 LANGUAGES CXX)


include(CTest)
find_package(GTest REQUIRED)#comes with CMake
if(GTEST_FOUND)
	include(GoogleTest)
else(GTEST_FOUND)
	message(FATAL_ERROR "DANGER: Could not find GoogleTest")
endif(GTEST_FOUND)

#Benchmarking
find_package(GBench REQUIRED)
if(NOT GBENCH_FOUND)
	message(FATAL_ERROR "DANGER: Could not find GoogleBenchmark")
endif(NOT GBENCH_FOUND)


#TESTING
add_executable(run_tests "alltests.cpp" )
target_link_libraries(run_tests naivelinalg common )
target_link_libraries(run_tests multiply_solution transpose_solution openmp_solution )
target_link_libraries(run_tests GTest::GTest GTest::Main)#CMake 3.12
gtest_discover_tests(run_tests)

#BENCHMARKING
add_executable(run_benchmarks "allbench.cpp")
target_link_libraries(run_benchmarks naivelinalg common )
target_link_libraries(run_benchmarks  multiply_solution transpose_solution openmp_solution )
target_link_libraries(run_benchmarks GBench::gbench GBench::gbench_main)

#TILE SIZE SEARCH
add_executable(find_tile_size "find_tile_size.cpp")
target_link_libraries(find_tile_size naivelinalg common )
target_link_libraries(find_tile_size  multiply_solution transpose_solution openmp_solution )
target_link_libraries(find_tile_size GBench::gbench GBench::gbench_main)

#CUSTOM BENCHMARKS
add_executable(student_benchmarks "student_benchmarks.cpp")
target_link_libraries(student_benchmarks naivelinalg common )
target_link_libraries(student_benchmarks  multiply_solution transpose_solution openmp_solution )
target_link_libraries(student_benchmarks GBench::gbench GBench::gbench_main)
