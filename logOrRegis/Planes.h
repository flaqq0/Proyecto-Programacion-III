#ifndef PROYECTOLIMPIO_PLANES_H
#define PROYECTOLIMPIO_PLANES_H
#include "../librerias.h"

struct Planes {
    double precio;
    string name, quality, resolution;
    bool spatialAudio;
    int devicesSameT, downloadDevices;

    Planes();
    Planes(string name, double price, string qual, string resol, bool spatialAudio, int devicessametime, int download);

    string getName()const;
    double getPrecio()const;
    string getQuality()const;
    string getResolution()const;
    bool getSpatialAudio()const;
    int getDevicesSameTime()const;
    int getDownloadDevices()const;
};

class Premium : virtual public Planes{
public:
    Premium();
    Premium(const string &name, double price, const string &qual, const string &resol, bool spatialAudio,
            int devicessametime, int download);
};
class Standard : virtual public Planes {
public:
    Standard();
    Standard(const string &name, double price, const string &qual, const string &resol, bool spatialAudio,
             int devicessametime, int download);
};
class Basic : virtual public Planes {
public:
    Basic();
    Basic(const string &name, double price, const string &qual, const string &resol, bool spatialAudio,
          int devicessametime, int download);
};

#endif