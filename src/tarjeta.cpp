#include "tarjeta.h"

Tarjeta::Tarjeta() {}

bool Tarjeta::init() {
  if (!SD.begin()) {
    return false;
  }
  return true;
}

bool Tarjeta::comprobar(const char* nombreArchivo) {
  return SD.exists(nombreArchivo);
}

bool Tarjeta::abrir(const char* nombreArchivo) {
  archivo = SD.open(nombreArchivo, FILE_WRITE);
  if (!archivo) {
    return false;
  }
  return true;
}

bool Tarjeta::escribir(const String& datos) {
  if (!archivo) {
    return false;
  }
  archivo.println(datos);
  archivo.flush();
  return true;
}

void Tarjeta::obtenerMaximos(double& maxTemperatura, double& maxPresion) {
  maxTemperatura = -999.0; // Valor inicial mínimo para buscar el máximo
  maxPresion = -999.0;     // Valor inicial mínimo para buscar el máximo

  archivo.seek(0); // Reiniciar la lectura desde el principio del archivo

  while (archivo.available()) {
    String linea = archivo.readStringUntil('\n');

    // Extraer los datos de la línea
    int primerPunto = linea.indexOf(';');
    int segundoPunto = linea.indexOf(';', primerPunto + 1);
    int tercerPunto = linea.indexOf(';', segundoPunto + 1);

    String temperaturaStr = linea.substring(segundoPunto + 1, tercerPunto);
    String presionStr = linea.substring(tercerPunto + 1);

    double temperatura = temperaturaStr.toDouble();
    double presion = presionStr.toDouble();

    // Actualizar los máximos
    if (temperatura > maxTemperatura) {
      maxTemperatura = temperatura;
    }

    if (presion > maxPresion) {
      maxPresion = presion;
    }
  }
}

