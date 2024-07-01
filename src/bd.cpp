#include "bd.h"
#include <fstream>
#include <sstream>
#include <iostream>

//Manejo de errores
vector<Pelicula> cargarBaseDatos(const string& archivo) {
    vector<Pelicula> peliculas;
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return peliculas;
    }

    string linea;
    while (getline(file, linea)) { //lee linea a linea
        stringstream ss(linea);
        string titulo, sinopsis, tagsStr;
        getline(ss, titulo, ','); //extrae titulo hasta la 1er coma
        getline(ss, sinopsis, ',');
        getline(ss, tagsStr);

        vector<string> tags;
        stringstream ssTags(tagsStr);
        string tag;
        while (getline(ssTags, tag, ';')) {
            tags.push_back(tag);
        }

        peliculas.emplace_back(titulo, sinopsis, tags);
    }
    file.close();
    return peliculas;
}