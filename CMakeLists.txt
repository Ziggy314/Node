
cmake_minimum_required(VERSION 3.16.3)

project(Node)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

set(CMAKE_BUILD_TYPE Debug)
include_directories(/headers)
add_executable ( Node main.cpp )

