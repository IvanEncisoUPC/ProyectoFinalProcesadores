#ifndef TARJETASD_H
#define TARJETASD_H

#include <SPI.h>
#include <SD.h>

class TarjetaSD {
public:
  void iniciar();
  bool archivoExiste();
  void crearArchivo();
  void abrirArchivo();
  void escribirRegistro(float temperatura, float presion);
  void cerrarArchivo();
  void obtenerMaximos(float& presionMaxima, float& temperaturaMaxima);

private:
  File archivoDatos;
};

#endif
