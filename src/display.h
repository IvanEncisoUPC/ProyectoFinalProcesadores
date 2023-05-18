#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>   

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

class Display{
  private:
    Adafruit_SSD1306 display;

  public:
    Display() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {}
    void init();
    void showTemperature(float temperature);
    void showPressure(float pressure);
    void clearreset();
};

#endif