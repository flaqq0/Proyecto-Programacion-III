#include "MovieSearch.h"
#include <iostream>

int main() {
    Buscador& engine = Buscador::getInstance();

    try {
        engine.loadCSV("C:/Users/sofia/Desktop/Documentos/2024/progra 3/proyecto-prueba/peliculas.csv");
    } catch (const std::exception& e) {
        cout << "Error loading CSV: " << e.what() << std::endl;
        return 1;
    }

    engine.addEstrategia(make_unique<PorTitulo>());
    engine.addEstrategia(make_unique<PorTag>());
    engine.addEstrategia(make_unique<PorPlot>());
    while(true) {
        string query;
        cout << "Buscar: ";
        cin >> query;

        auto res = engine.buscar(query);

        for (const auto &movie: res) {
            cout << "IMDB ID: " << movie.imdb_id << "\n" << "Title: " << movie.title << "\n" << "Tags: " << movie.tags
                 << "\n\n";
        }
    }

}
