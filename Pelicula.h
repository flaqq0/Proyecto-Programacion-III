#ifndef PROYECTO_PROGRAMACION_III_PELICULA_H
#define PROYECTO_PROGRAMACION_III_PELICULA_H

#include "librerias.h"
using namespace std;

class Pelicula {
public:
    string titulo;
    string sinopsis;
    vector<string> tags;

    Pelicula(string titulo, string sinopsis, vector<string> tags)
            : titulo(titulo), sinopsis(sinopsis), tags(tags) {}

    void mostrar() const {
        cout << "Titulo: " << titulo << endl;
        cout << "Sinopsis: " << sinopsis << endl;
        cout << "Tags: ";
        for(const auto& tag : tags) {
            cout << tag << " ";
        }
        cout << endl;
    }
};

#endif //PROYECTO_PROGRAMACION_III_PELICULA_H
