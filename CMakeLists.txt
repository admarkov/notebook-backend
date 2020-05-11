cmake_minimum_required(VERSION 3.16)
project(notebook_backend)

set(CMAKE_CXX_STANDARD 17)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} vendor)
add_executable(notebook_backend main.cpp)