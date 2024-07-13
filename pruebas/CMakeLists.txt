cmake_minimum_required(VERSION 3.26)
project(proyecto_prueba)

set(CMAKE_CXX_STANDARD 17)

add_executable(a1 prueba1.cpp)
add_executable(a2 prueba2.cpp
        MovieSearch.cpp
        MovieSearch.h)
