cmake_minimum_required(VERSION 3.25)
project(prac1)

set(CMAKE_CXX_STANDARD 17)
find_package(Parlay REQUIRED)

add_executable(prac1 main.cpp quick_sort_seq.h quick_sort_par.h)
