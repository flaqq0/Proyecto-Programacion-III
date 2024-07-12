#ifndef PROYECTOLIMPIO_CLEANDATA_H
#define PROYECTOLIMPIO_CLEANDATA_H

#include "librerias.h"
struct CMovie{
    string imdb_id,title,plot_synopsis,tags,split,synopsis_source;
};
vector<CMovie>loadCsv(const string& nombreFile);

#endif //PROYECTOLIMPIO_CLEANDATA_H
