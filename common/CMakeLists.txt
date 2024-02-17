cmake_minimum_required (VERSION 3.5)
project(mp1-common VERSION 1.0.0 LANGUAGES C)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

#our linear algebra library
add_library(naivelinalg OBJECT "naivelinalg.c" "naivelinalg.h")
target_link_libraries(naivelinalg PUBLIC m)
target_include_directories(naivelinalg PUBLIC "./")

#TODO: investigate fixing the linker and having this be an OBJECT
add_library(common STATIC "util.c" "basic.c")
target_link_libraries(common PUBLIC naivelinalg)
target_include_directories(common PUBLIC "./")
