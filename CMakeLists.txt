cmake_minimum_required(VERSION 3.26)
project(proyecto)

set(CMAKE_CXX_STANDARD 17)


add_executable(a h.cpp librerias.h)
add_executable(busqueda busqueda.cpp peliculas.csv)
add_executable(pt2 bd.cpp bd.h buscador.cpp buscador.h utilidades.cpp utilidades.h)