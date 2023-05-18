#ifndef TARJETA_H
#define TARJETA_H

#include <SD.h>
#include <SPI.h>

class Tarjeta{
    private: 
        File file;
        const char*filename;

    public: 
    SD(const char*filename);

    bool begin();
    //bool comprobar();
    void abrir();
    void writeData(String hora, String fecha, float pres, float temp);
    void closeFile();
    void getMaxValues(float & maxPres, float & maxTemp);
};

#endif