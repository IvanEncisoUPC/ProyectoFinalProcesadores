#ifndef MOSQUITO_H
#define MOSQUITO_H

#include <WiFi.h>
#include <PubSubClient.h>

class Mosquito {
  public:
    Mosquito(const char* mqttServer, int mqttPort, const char* mqttUsername, const char* mqttPassword);
    bool connectWiFi(const char* ssid, const char* password);
    void connectMQTT();
    bool isConnected();
    void publish(const char* topic, const char* payload);
    void loop();

  private:
    const char* mqttServer;
    int mqttPort;
    const char* mqttUsername;
    const char* mqttPassword;
    WiFiClient wifiClient;
    PubSubClient mqttClient;
};

#endif
