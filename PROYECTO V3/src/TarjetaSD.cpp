#include "TarjetaSD.h"

void TarjetaSD::iniciar() {
  if (!SD.begin(5)) {
    Serial.println("Error al montar la tarjeta SD");
    return;
  }
  Serial.println("Tarjeta SD inicializada");
}

bool TarjetaSD::archivoExiste() {
  return SD.exists("/datos.csv");
}

void TarjetaSD::crearArchivo() {
  archivoDatos = SD.open("/datos.csv", FILE_WRITE);
  archivoDatos.close();
  Serial.println("Archivo creado");
}

void TarjetaSD::abrirArchivo() {
  archivoDatos = SD.open("/datos.csv", FILE_WRITE);
}

void TarjetaSD::escribirRegistro(float temperatura, float presion) {
  String registro = "";

  //registro += String(year()) + "-";
  //registro += String(month()) + "-";
  //registro += String(day()) + ";";
  //registro += String(hour()) + ":";
  //registro += String(minute()) + ":";
  //registro += String(second()) + ";";
  registro += String(presion) + ";";
  registro += String(temperatura) + "\n";

  archivoDatos.println(registro);
  archivoDatos.flush();
}

void TarjetaSD::cerrarArchivo() {
  archivoDatos.close();
}

void TarjetaSD::obtenerMaximos(float& presionMaxima, float& temperaturaMaxima) {
  presionMaxima = -1;
  temperaturaMaxima = -100;

  archivoDatos = SD.open("/datos.csv");

  if (archivoDatos) {
    while (archivoDatos.available()) {
      String linea = archivoDatos.readStringUntil('\n');
      int primerSeparador = linea.indexOf(';');
      int segundoSeparador = linea.indexOf(';', primerSeparador + 1);
      float presion = linea.substring(primerSeparador + 1, segundoSeparador).toFloat();
      float temperatura = linea.substring(segundoSeparador + 1).toFloat();

      if (presion > presionMaxima) {
        presionMaxima = presion;
      }

      if (temperatura > temperaturaMaxima) {
        temperaturaMaxima = temperatura;
      }
    }
    archivoDatos.close();
  } else {
    Serial.println("Error al abrir datos.csv");
  }
}
