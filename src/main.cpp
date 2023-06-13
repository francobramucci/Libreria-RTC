#include "rtcpoli.h"

void setup() {
    Wire.begin();           // Inicializar la comunicación I2C
    Serial.begin(9600);     // Inicializar la comunicación serial
    Serial.println("Fecha y Tiempo al momento de compilacion: " + String(__TIME__) + " " + String(__DATE__));
    setDateTime(getCompDateTime(__TIME__, __DATE__));
}

void loop() {
    DateTime time = getTime(RTC_ADDRESS, DS3231_TIME);

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
        
    delay(1000);  // Esperar antes de leer el siguiente segundo
}
