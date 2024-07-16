cmake_minimum_required(VERSION 3.26)
project(proyecto_prueba)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(a1 prueba1.cpp)
add_executable(a2 prueba2.cpp
        ../MovieSearch.cpp
        ../MovieSearch.h librerias.h cleanData.cpp cleanData.h)
add_executable(a3 prueba3.cpp)
add_executable(a4 prueba4.cpp)