cmake_minimum_required(VERSION 3.19)
project(P5_CLion)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(P5_CLion main.cpp Node.h BinarySearchTree.h Util.h)