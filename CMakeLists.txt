
cmake_minimum_required(VERSION 3.16.3)
include(CMakePrintHelpers)

project(Node)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)


find_package(benchmark REQUIRED)


set(CMAKE_BUILD_TYPE Debug)
include_directories(
    /NodeImpl
    /Nodes
    )
add_executable ( Node main.cpp )

target_link_libraries(Node benchmark::benchmark)
