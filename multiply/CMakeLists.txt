cmake_minimum_required (VERSION 3.5)
project(mp1-multiply VERSION 1.0.0 LANGUAGES CXX)


add_library(multiply_solution OBJECT "multiply.cpp")
target_link_libraries(multiply_solution common)
target_include_directories(multiply_solution PUBLIC "./")

add_executable(multiply_runner "main.cpp" )
target_link_libraries(multiply_runner multiply_solution common)
