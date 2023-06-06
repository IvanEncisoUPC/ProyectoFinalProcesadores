#include "Sensor.h"

void Sensor::iniciar() {
  if (!bmp.begin(0x76)) {
    Serial.println("No se pudo encontrar un sensor BMP280 válido, ¡verifica la conexión!");
    while (1);
  }
}

float Sensor::leerTemperatura() {
  return bmp.readTemperature();
}

float Sensor::leerPresion() {
  return bmp.readPressure() / 100.0F;
}
