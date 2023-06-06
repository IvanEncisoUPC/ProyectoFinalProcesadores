#include "Mosquito.h"

void Mosquito::setServidor(const char* servidor, int puerto) {
  servidorMQTT = servidor;
  puertoMQTT = puerto;
}

void Mosquito::setCredenciales(const char* usuario, const char* pass) {
  usuarioMQTT = usuario;
  passMQTT = pass;
}

void Mosquito::conectar() {
  clienteMQTT.setClient(clienteWiFi);
  clienteMQTT.setServer(servidorMQTT, puertoMQTT);

  while (!clienteMQTT.connected()) {
    Serial.println("Conectando a MQTT...");
    if (clienteMQTT.connect("ESP32_Cliente", usuarioMQTT, passMQTT)) {
      Serial.println("Conectado a MQTT");
    } else {
      Serial.print("Error al conectar a MQTT, estado: ");
      Serial.println(clienteMQTT.state());
      delay(2000);
    }
  }
}

void Mosquito::reconectar() {
  while (!clienteMQTT.connected()) {
    Serial.println("Conexión perdida. Intentando reconectar...");
    if (clienteMQTT.connect("ESP32_Cliente", usuarioMQTT, passMQTT)) {
      Serial.println("Reconectado a MQTT");
    } else {
      Serial.print("Error al reconectar a MQTT, estado: ");
      Serial.println(clienteMQTT.state());
      delay(2000);
    }
  }
}

void Mosquito::publicar(const char* topic, const char* mensaje) {
  if (!clienteMQTT.connected()) {
    reconectar();
  }

  if (clienteMQTT.publish(topic, mensaje)) {
    Serial.print("Publicado en ");
    Serial.print(topic);
    Serial.print(": ");
    Serial.println(mensaje);
  } else {
    Serial.println("Error al publicar en MQTT");
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Lógica de procesamiento del mensaje recibido
}