cmake_minimum_required(VERSION 3.20)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TicTacToe
        getch.h
        main.cpp)
