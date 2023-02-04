cmake_minimum_required(VERSION 3.24)
project(ascii_map)

include_directories("src")

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(AsciiMap main.cpp)
