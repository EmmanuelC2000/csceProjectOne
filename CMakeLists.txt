cmake_minimum_required(VERSION 3.17)
project(projectOne)

set(CMAKE_CXX_STANDARD 17)
set(Sources projectFunctions.cpp)
set(Headers functionDeclarations.h)

add_executable(projectOne main.cpp)