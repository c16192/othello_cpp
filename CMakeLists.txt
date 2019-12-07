cmake_minimum_required(VERSION 3.15)
project(othello)

set(CMAKE_CXX_STANDARD 14)

FILE(GLOB SOURCES src/*.cpp src/**/*.cpp src/*.h src/**/*.h)
ADD_EXECUTABLE(othello ${SOURCES})