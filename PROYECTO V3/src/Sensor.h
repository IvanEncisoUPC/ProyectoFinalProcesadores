#ifndef SENSOR_H
#define SENSOR_H

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

class Sensor {
public:
  void iniciar();
  float leerTemperatura();
  float leerPresion();

private:
  Adafruit_BMP280 bmp;
};

#endif
