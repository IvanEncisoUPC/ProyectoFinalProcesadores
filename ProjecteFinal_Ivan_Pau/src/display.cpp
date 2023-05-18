#include "display.h"

void Display::init() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("BMP280 + SSD1306");
  display.display();
  delay(2000);
}

void Display::clearreset(){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
}

void Display::showTemperature(float temperature) {
  display.println("Temp: ");
  display.print(temperature);
  display.println(" C");
  display.display();
}

void Display::showPressure(float pressure) {
  display.println("Pres: ");
  display.print(pressure);
  display.println(" hPa");
  display.display();
}