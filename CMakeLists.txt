cmake_minimum_required(VERSION 3.21)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 14)

include_directories(extern)
include_directories(extern/conio)

add_executable(TicTacToe
        extern/conio/conio.h
        main.cpp)
