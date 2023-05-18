#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>
#include "display.h"
#include "sensor.h"

Display dis;
Sensor sen;

void setup() {
  Serial.begin(115200);
  dis.init();
  sen.init();
  dis.clearreset();
}

void loop() {
  float temperature = sen.readTemperature();
  float pressure = sen.readPressure();

  dis.clearreset();
  dis.showTemperature(temperature);
  dis.showPressure(pressure);
  delay(1000);
}