cmake_minimum_required(VERSION 3.26)
project(proyecto)

set(CMAKE_CXX_STANDARD 17)

add_executable(proyecto
        main.cpp
        Pelicula.cpp
        bd.cpp
        buscador.cpp
        Utilidades.cpp
)

