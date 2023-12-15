cmake_minimum_required(VERSION 3.25)
project(prac2)

set(CMAKE_CXX_STANDARD 17)
find_package(Parlay REQUIRED)

add_executable(prac2 main.cpp bfs_seq.h bfs_par.h)
