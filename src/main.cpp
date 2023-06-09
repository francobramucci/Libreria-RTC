#include <Arduino.h>
#include <Wire.h>

typedef struct{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year; 

}DateTime;

byte bcdToDec(byte bcd) {
  return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

#define RTC_ADDRESS 0x68  // Dirección I2C del RTC DS1307/3231

void setup() {
  Wire.begin();  // Inicializar la comunicación I2C
  Serial.begin(9600);  // Inicializar la comunicación serial
}

/*
  Con esta función comunicaremos desde donde queremos empezar
  a leer para posteriormente hacer una solicitud y obtener la 
  información de la fecha en formato de 24 horas
*/

DateTime getTime(byte rtc_addr){
  Wire.beginTransmission(rtc_addr);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(rtc_addr, 7); //Pido 7 bytes, partiendo de 00h hasta 06h
  
  DateTime dateTime;
  
  if (Wire.available()) {
    dateTime.second = bcdToDec(Wire.read() & 0x7F);
    dateTime.minute = bcdToDec(Wire.read());
    dateTime.hour = bcdToDec(Wire.read() & 0x3F);
    dateTime.dayOfWeek = bcdToDec(Wire.read());
    dateTime.dayOfMonth = bcdToDec(Wire.read());
    dateTime.month = bcdToDec(Wire.read());
    dateTime.year = bcdToDec(Wire.read());
  }
  return dateTime;
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