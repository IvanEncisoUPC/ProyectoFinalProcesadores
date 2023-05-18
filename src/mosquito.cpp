#include "Mosquito.h"

Mosquito::Mosquito(const char* mqttServer, int mqttPort, const char* mqttUsername, const char* mqttPassword)
    : mqttServer(mqttServer), mqttPort(mqttPort), mqttUsername(mqttUsername), mqttPassword(mqttPassword),
      mqttClient(wifiClient) {
}

bool Mosquito::connectWiFi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    retries++;
    if (retries > 10) {
      return false;
    }
  }
  return true;
}

void Mosquito::connectMQTT() {
  mqttClient.setServer(mqttServer, mqttPort);
  while (!mqttClient.connected()) {
    if (mqttClient.connect("ESP32Client", mqttUsername, mqttPassword)) {
      // Conexión exitosa
    } else {
      delay(5000); // Esperar antes de intentar nuevamente
    }
  }
}

bool Mosquito::isConnected() {
  return mqttClient.connected();
}

void Mosquito::publish(const char* topic, const char* payload) {
  mqttClient.publish(topic, payload);
}

void Mosquito::loop() {
  if (!mqttClient.connected()) {
    connectMQTT();
  }
  mqttClient.loop();
}
