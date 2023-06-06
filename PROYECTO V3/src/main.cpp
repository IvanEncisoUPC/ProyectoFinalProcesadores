#include <WiFi.h>
#include <PubSubClient.h>
#include "Display.h"
#include "Sensor.h"
#include "TarjetaSD.h"
#include "Mosquito.h"

const char* ssid = "Iwaiin";
const char* password = "12345678";
const char* mqtt_server = "d20ee00a.ala.us-east-1.emqxsl.com";
const int mqtt_port = 8883;
const char* mqtt_user = "ESP32";
const char* mqtt_password = "12345678";
const char* topic_temperatura = "temperatura";
const char* topic_presion = "presion";
const int botonPin = 2;

WiFiClient espClient;
PubSubClient client(espClient);
Display display;
Sensor sensor;
TarjetaSD tarjetaSD;
Mosquito mosquito;

float temperaturaMaxima, presionMaxima;

void setup() {
  Serial.begin(115200);

  pinMode(botonPin, INPUT_PULLDOWN);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi");

  Serial.println("Inicair cliente MQTT");
  client.setServer(mqtt_server, mqtt_port);
  Serial.println("Conexcion con MQTT realizada");
  
  
  display.iniciar();
  Serial.println("Display inicializado");
  tarjetaSD.iniciar();
  Serial.println("Setear Servidor y credenciales MQTT");
  mosquito.setServidor(mqtt_server, mqtt_port);
  mosquito.setCredenciales(mqtt_user, mqtt_password);
  Serial.println("Servidor y credenciales generados");

  Serial.println("Comprobando existencia de archivo");
  if (!tarjetaSD.archivoExiste()) {
    tarjetaSD.crearArchivo();
  }

  sensor.iniciar();
  Serial.println("Sensor iniciado");
  display.limpiar();

  Serial.println("Obteniendo datos maximos");
  tarjetaSD.obtenerMaximos(presionMaxima, temperaturaMaxima);
}

void loop() {
  Serial.println("Loop iniciado");
  if (!client.connected()) {
    mosquito.setServidor(mqtt_server, mqtt_port);
    mosquito.setCredenciales(mqtt_user, mqtt_password);
  }
  client.loop();

  Serial.println("Comprobacion del boton");
  if (digitalRead(botonPin) == HIGH) {
    display.mostrarTemperatura(temperaturaMaxima);
    display.mostrarPresion(presionMaxima);
  } else {
    Serial.println("Leyendo valores del sensor");
    float temperatura = sensor.leerTemperatura();
    float presion = sensor.leerPresion();
    Serial.println("Comparando valores leidos con maximos");
    if(temperatura >= temperaturaMaxima){
      temperaturaMaxima = temperatura;
    }
    if(presion >= presionMaxima){
      presionMaxima = presion;
    }
    Serial.print("Temperatura = ");
    Serial.println(temperatura);
    Serial.print("Presion = ");
    Serial.println(presion);
    display.mostrarTemperatura(temperatura);
    display.mostrarPresion(presion);
    tarjetaSD.abrirArchivo();
    tarjetaSD.escribirRegistro(temperatura, presion);
    tarjetaSD.cerrarArchivo();

    mosquito.conectar();
    mosquito.publicar(topic_temperatura, String(temperatura).c_str());
    mosquito.publicar(topic_presion, String(presion).c_str());
  }
  delay(1000);
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Conectando a MQTT...");
    if (client.connect("ESP32_Cliente", mqtt_user, mqtt_password)) {
      Serial.println("Conectado a MQTT");
      client.subscribe(topic_temperatura);
      client.subscribe(topic_presion);
    } else {
      Serial.print("Error al conectar a MQTT, estado: ");
      Serial.println(client.state());
      delay(5000);
    }
  }
}



