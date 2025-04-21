cmake_minimum_required(VERSION 3.31)
project(edge_covers C)

find_path(GMP_INCLUDE_DIR NAMES gmp.h)
find_library(GMP_LIBRARY NAMES gmp)

set(CMAKE_C_STANDARD 17)

add_executable(edge_covers edge_covers.c)
target_include_directories(edge_covers PRIVATE ${GMP_INCLUDE_DIR})
target_link_libraries(edge_covers PRIVATE ${GMP_LIBRARY})