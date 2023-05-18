#ifndef SENSOR_H
#define SENSOR_H

#include <Adafruit_BMP280.h>

class Sensor{
  private:
    Adafruit_BMP280 bmp;

  public:
    void init();
    float readTemperature();
    float readPressure();
};

#endif