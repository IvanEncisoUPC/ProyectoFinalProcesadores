#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Display {
public:
  void iniciar();
  void limpiar();
  void mostrarTemperatura(float temperatura);
  void mostrarPresion(float presion);

private:
  Adafruit_SSD1306 display;
};

#endif
