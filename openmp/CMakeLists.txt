cmake_minimum_required (VERSION 3.5)
project(mp1-openmp VERSION 1.0.0 LANGUAGES CXX)


find_package(OpenMP REQUIRED)

add_library(openmp_solution OBJECT "openmp.cpp")
target_link_libraries(openmp_solution common OpenMP::OpenMP_CXX)
target_include_directories(openmp_solution PUBLIC "./")

#Students might want to override the fatal error above and this lets them compile everything else.
add_executable(openmp_runner "main.cpp" )
target_link_libraries(openmp_runner openmp_solution common)
