#include "Tarjeta.h"

Tarjeta::Tarjeta(const char* filename) {
  this->filename = filename;
}

bool Tarjeta::begin() {
  if (!SD.begin()) {
    return false;
  }
  return true;
}

bool Tarjeta::comprobar() {
  return SD.exists(filename);
}

void Tarjeta::abrir() {
  file = SD.open(filename, FILE_WRITE);
}

void Tarjeta::escribir(String hora, String fecha, float pres, float temp) {
  String datos;
  data.concat(fecha);
  data.concat(";");
  data.concat(hora);
  data.concat(";");
  data.concat(pres);
  data.concat(";");
  data.concat(temp);
  
  if (file) {
    file.println(datos);
  }
}

void Tarjeta::cerrar() {
  file.close();
}