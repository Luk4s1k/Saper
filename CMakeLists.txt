cmake_minimum_required(VERSION 3.17)
project(MineSaper)

set(CMAKE_CXX_STANDARD 14)

add_executable(MineSaper main.cpp MinesweeperBoard.cpp MinesweeperBoard.h MSBoardTextView.cpp MSBoardTextView.h MSTextController.cpp MSTextController.h)