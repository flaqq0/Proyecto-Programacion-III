#include <iostream>
#include <future>
#include "Pelicula.h"
#include "bd.h"
#include "buscador.h"
#include "utilidades.h"
using namespace std;

template<typename Func, typename Criterio> //se pasan los metodos de buscador como parametro
void mostrarTitulosPeliculas(Func func, const vector<Pelicula>& peliculas, const Criterio& criterio) {
    auto resultados_Futuro = async(launch::async, func, ref(peliculas), criterio);
    vector<Pelicula> resultados = resultados_Futuro.get();

    cout << "Títulos de las primeras 5 películas resultado de tu busqueda:" << endl;
    for (size_t i = 0; i < min(resultados.size(), size_t(5)); i++) {
        cout << (i+1) << ". " << resultados[i].titulo << endl;
    }
}

int main() {
    vector<Pelicula> peliculas = cargarBaseDatos("peliculas.csv");

    int opcion;
    do {
        cout << "------------¡Bienvenido a tu plataforma de streaming!--------------" << endl;
        cout << "Ingresa el número de la opción para el tipo de búsqueda que deseas realizar" << endl;
        cout << "1. Buscar por el nombre de la película" << endl;
        cout << "2. Buscar por el Tag de la película" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;
        cin.ignore();

        if (opcion != 1 && opcion != 2) {
            cout << "Opción no válida (Solo se admiten opciones 1 o 2)" << endl;
        }

    } while (opcion != 1 && opcion != 2);

    if (opcion == 1) {
        string palabraClave;
        cout << "Ingrese el título de la película: ";
        getline(cin, palabraClave);

        mostrarTitulosPeliculas(buscarPorTitulo, peliculas, palabraClave);
    } else if (opcion == 2) {
        string tag;
        cout << "Ingrese un tag para buscar películas: ";
        getline(cin, tag);

        mostrarTitulosPeliculas(buscarPorTag, peliculas, tag);
    }

    vector<string> likes = obtenerTagsFavoritos();
    auto recomendacionesFuturo = async(launch::async, recomendarPeliculas, ref(peliculas), likes);
    vector<Pelicula> recomendaciones = recomendacionesFuturo.get();
    cout << "Recomendaciones basadas en sus likes dados: " << endl;
    mostrarTitulosPeliculas(recomendarPeliculas, peliculas, likes);

    return 0;
}
