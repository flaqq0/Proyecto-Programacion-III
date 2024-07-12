#include "Planes.h"
Planes::Planes() {}
Planes::Planes(string name, double price, string qual, string resol, bool spatialAudio,
               int devicessametime, int download) : name(name), precio(price), quality(qual), resolution(resol),
               spatialAudio(spatialAudio), devicesSameT(devicessametime), downloadDevices(download) {}

string Planes::getName() const {return name;}
double Planes::getPrecio() const {return precio;}
string Planes::getQuality() const {return quality;}
string Planes::getResolution() const {return resolution;}
bool Planes::getSpatialAudio() const {return spatialAudio;}
int Planes::getDevicesSameTime() const {return devicesSameT;}
int Planes::getDownloadDevices() const {return downloadDevices;}

Premium::Premium() = default;
Premium::Premium(const string &name, double price, const string &qual, const string &resol, bool spatialAudio,
                 int devicessametime, int download) : Planes(name, price, qual, resol, spatialAudio, devicessametime, download) {}
Standard::Standard() = default;
Standard::Standard(const string &name, double price, const string &qual, const string &resol, bool spatialAudio,
                   int devicessametime, int download) : Planes(name, price, qual, resol, spatialAudio, devicessametime,download) {}

Basic::Basic() = default;
Basic::Basic(const string &name, double price, const string &qual, const string &resol, bool spatialAudio,
             int devicessametime, int download) : Planes(name, price, qual, resol, spatialAudio, devicessametime,
                                                         download) {}