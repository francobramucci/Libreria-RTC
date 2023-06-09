#include "rtcpoli.h"

void setup() {
  Wire.begin();  // Inicializar la comunicación I2C
  Serial.begin(9600);  // Inicializar la comunicación serial
}

void loop() {
  
  DateTime time = getTime(0x68);

  Serial.print("Fecha: ");
  Serial.print(time.hour);
  Serial.print(":");
  Serial.print(time.minute);
  Serial.print(":");
  Serial.print(time.second);
  Serial.print(" ");
  Serial.print(time.dayOfMonth);
  Serial.print("/");
  Serial.print(time.month);
  Serial.print("/");
  Serial.print(time.year);
  Serial.println("");
  delay(1000);  // Esperar antes de leer el siguiente registro
}