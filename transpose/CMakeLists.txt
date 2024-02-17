cmake_minimum_required (VERSION 3.5)
project(mp1-transpose VERSION 1.0.0 LANGUAGES CXX)

add_library(transpose_solution OBJECT "transpose.cpp")
target_link_libraries(transpose_solution PUBLIC common)
target_include_directories(transpose_solution PUBLIC "./")

add_executable(transpose_runner "main.cpp" )
target_link_libraries(transpose_runner PUBLIC transpose_solution common)
