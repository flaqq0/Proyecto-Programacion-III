#ifndef PROYECTO_PROGRAMACION_III_BUSCADOR_H
#define PROYECTO_PROGRAMACION_III_BUSCADOR_H

#include <algorithm>
#include <future>
#include "Pelicula.h"
using namespace std;

template<typename Predicate>
vector<Pelicula> buscar(const vector<Pelicula>& peliculas, Predicate respuesta);

vector<Pelicula> buscarPorTitulo(const vector<Pelicula>& peliculas, const string& palabraClave);
vector<Pelicula> buscarPorTag(const vector<Pelicula>& peliculas, const string& tag);
vector<Pelicula> recomendarPeliculas(const vector<Pelicula>& peliculas, const vector<string>& likes);

#endif //PROYECTO_PROGRAMACION_III_BUSCADOR_H
