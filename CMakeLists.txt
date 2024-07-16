cmake_minimum_required(VERSION 3.10)
project(ProyectoLimpio)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/cpp-httplib)
add_executable(ProyectoLimpio main.cpp
        cleanData.cpp
        cleanData.h
)

target_link_libraries(ProyectoLimpio PRIVATE httplib::httplib)