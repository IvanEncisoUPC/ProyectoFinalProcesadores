#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>
#include <RTClib.h> //Real Time Clock
#include "display.h"
#include "sensor.h"
#include "tarjeta.h"

RTC_DS3231 rtc();
Display dis();
Sensor sen();
Tarjeta tarjeta();
Mosquito mosquito("mqtt_server", 1883, "esp32", "123Esp32"); //Datos del servidor MQTT

const char* ssid = "iwaiin";
const char* password = "12345678";

const int buttonPin = 2; // Pin del botónc (Es posible que se cambie en un futuro)
bool buttonPressed = false;

void setup() {
  Serial.begin(115200);
  dis.init(); //Inicializar el display
  sen.init(); //Inicialiozar el sensor
  mosquito.connectWiFi(ssid, password); // Conectar a la red WiFi
  tarjeta.begin(); // Inicializar la tarjeta SD
  rtc.begin();

  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING); // Asignar la interrupción al botón

  dis.clearreset();//Limpieza del display
}

void loop() {
  DateTime now = rtc.now(); //Obtencion de la hora y fecha actuales

  float temperature = sen.readTemperature(); //Leer la temperatura del sensor
  float pressure = sen.readPressure(); //Leer la presion del sensor

  dis.clearreset();

  if (mosquito.isConnected()) {
    // Publicar datos en el servidor MQTT
    char topic[50];
    char payload[50];
    snprintf(topic, sizeof(topic), "temperatura"); //Creacion del topic temperatura
    snprintf(payload, sizeof(payload), "%.2f", temperature); //Creacion del valor de temperatura
    mosquito.publish(topic, payload); //Publicacion de la temperatura
  
    snprintf(topic, sizeof(topic), "presion"); //Creacion del topic presion
    snprintf(payload, sizeof(payload), "%.2f", pressure); //Creacion del valor de presion
    mosquito.publish(topic, payload); //Publicacion de la presion
  }

  String hora = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  String fecha = String(now.year()) + "/" + String(now.month()) + "/" + String(now.day());

  tarjeta.escribir(hora, fecha, pressure, temperature);

  if (buttonPressed) {
    float maxPressure, maxTemperature; //Variables para lectura del maximo

    tarjeta.maximos(maxPressure, maxTemperature); //Obtencion de los valores maximos de temperatura y presion

    dis.showTemperature(maxTemperature);
    dis.showPressure(maxPressure);
    
    buttonPressed = false;
  } 
  
  else {
    dis.showTemperature(temperature);
    dis.showPressure(pressure);
  }

  mosquito.loop(); //Para mantener la conexion del mosquito activa mas que nada.

  delay(1000);
}

//Interrupcion par ale boton
void buttonInterrupt() {
  buttonPressed = true;
}