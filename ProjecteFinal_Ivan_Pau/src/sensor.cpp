#include "sensor.h"

void Sensor::init() {
  bmp.begin(0x76);
}

float Sensor::readTemperature() {
  float temp = bmp.readTemperature();
  Serial.println(temp);
  return temp;
}

float Sensor::readPressure() {
  float pres = bmp.readPressure() / 100.0;
  Serial.println(pres);
  return pres;
}
