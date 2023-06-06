#include "Display.h"

void Display::iniciar() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("BMP280 + SSD1306");
  display.display();
  delay(2000);
}

void Display::limpiar() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
}

void Display::mostrarTemperatura(float temperatura) {
  display.println("Temp: ");
  display.print(temperatura);
  display.println(" C");
  display.display();
}

void Display::mostrarPresion(float presion) {
  display.println("Pres: ");
  display.print(presion);
  display.println(" hPa");
  display.display();
}
