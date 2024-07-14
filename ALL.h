#ifndef PROYECTOLIMPIO_ALL_H
#define PROYECTOLIMPIO_ALL_H

#include "logOrRegis/Planes.h"
#include "cleanData.h"

string fil = "D://Descargas//Proyecto-Programacion-III-main//Proyecto-Programacion-III//peliculas.csv";
vector<CMovie> movies = loadCsv(fil);

Premium premium("Premium", 44.90,"La mejor","4k(Ultra HD) + HDR", true, 4, 6);
Standard standard("Estándard",34.90,"Excelente","1080p (Full HD)",false,2,2);
Basic basic("Básico",24.90,"Buena","720p (HD)", false,1,1);


#endif