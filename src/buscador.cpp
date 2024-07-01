#include "buscador.h"
#include <algorithm>
#include <future>

//Progra generica, cree buscar usando template y uso esto en las 3 funciones siguientes de busqueda
template<typename Predicate>
vector<Pelicula> buscar(const vector<Pelicula>& peliculas, Predicate respuesta) {
    vector<Pelicula> resultados;
    for(const auto& pelicula : peliculas) {
        if (respuesta(pelicula)) {
            resultados.push_back(pelicula);
        }
    }
    sort(resultados.begin(), resultados.end(), [](const Pelicula& a, const Pelicula& b) { //ordena alfabeticamente
        return a.titulo < b.titulo;
    });
    return resultados;
}

vector<Pelicula> buscarPorTitulo(const vector<Pelicula>& peliculas, const string& palabraClave) {
    return buscar(peliculas, [&palabraClave](const Pelicula& pelicula) {
        return pelicula.titulo.find(palabraClave) != string::npos;
    });
}

vector<Pelicula> buscarPorTag(const vector<Pelicula>& peliculas, const string& tag) {
    return buscar(peliculas, [&tag](const Pelicula& pelicula) {
        return find(pelicula.tags.begin(), pelicula.tags.end(), tag) != pelicula.tags.end();
    });
}

vector<Pelicula> recomendarPeliculas(const vector<Pelicula>& peliculas, const vector<string>& likes) {
    return buscar(peliculas, [&likes](const Pelicula& pelicula) {
        for (const auto& like : likes) {
            if (find(pelicula.tags.begin(), pelicula.tags.end(), like) != pelicula.tags.end()) {
                return true;
            }
        }
        return false;
    });
}
