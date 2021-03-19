cmake_minimum_required(VERSION 3.15)
project(hicache)

set(CMAKE_CXX_STANDARD 11)
add_executable(hicache main.cpp Cache/cache.cpp Cache/cache.h)