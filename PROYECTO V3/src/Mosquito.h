#ifndef MOSQUITO_H
#define MOSQUITO_H

#include <WiFiClient.h>
#include <PubSubClient.h>

class Mosquito {
public:
  void setServidor(const char* servidor, int puerto);
  void setCredenciales(const char* usuario, const char* pass);
  void conectar();
  void reconectar();
  void publicar(const char* topic, const char* mensaje);

private:
  WiFiClient clienteWiFi;
  PubSubClient clienteMQTT;
  const char* servidorMQTT;
  int puertoMQTT;
  const char* usuarioMQTT;
  const char* passMQTT;
};

#endif