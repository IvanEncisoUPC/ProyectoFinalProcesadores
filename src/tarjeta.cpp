#ifndef TARJETA_H
#define TARJETA_H

#include <SD.h>
#include <SPI.h>

class Tarjeta{
    private: 
        File dataFile;
        const char*filename = "register.csv";
        
    public: 

    bool begin();
    bool comprobar();
    void abrir();
    void escribir(String hora, String fecha, float pres, float temp);
    void cerrar();
    void maximos(float & maxPres, float & maxTemp);
};

#endif