#ifndef TGARJETA_H
#define TARJETA_H

#include <SD.h>

class Tarjeta{
    private:

        File archivo;

    public:
        //Constructor
        Tarjeta();

        //Funciones
        bool init();
        bool comprobar(const char* archivo);
        void abrir(const char* archivo);
        //void cerrar(string archivo): //Esta funcionalidad no es necesaria ya que no necesitamos cerrar el archivo unicamente abriro.
        void escribir(const string & datos);
        void obtenerMaximos(double& maxTemperatura, double& maxPresion);
};

#endif