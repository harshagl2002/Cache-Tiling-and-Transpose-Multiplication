cmake_minimum_required (VERSION 3.5)
project(mp1 VERSION 1.0.0 LANGUAGES CXX)

# Location of additional cmake modules
#
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${PROJECT_SOURCE_DIR}/cmake
    )

include("cs484common")



#our linear algebra library
add_subdirectory("common")

#Student solutions
add_subdirectory("transpose")
add_subdirectory("multiply")
add_subdirectory("openmp")


#Tests

#this will also carry over to subdirectories
#include_directories("multiply" "transpose" "openmp")
add_subdirectory("tests")
