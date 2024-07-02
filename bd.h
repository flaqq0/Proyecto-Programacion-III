#ifndef PROYECTO_PROGRAMACION_III_BD_H
#define PROYECTO_PROGRAMACION_III_BD_H

#include "librerias.h"
#include "Pelicula.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

vector<Pelicula> cargarBaseDatos(const string& archivo);

#endif //PROYECTO_PROGRAMACION_III_BD_H
