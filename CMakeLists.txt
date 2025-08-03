cmake_minimum_required(VERSION 3.31)
project(huffman_coding)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")


add_executable(huffman_coding main.cpp
        Node.cpp
        Node.h
)
