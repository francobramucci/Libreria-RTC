#ifndef rtc_H
    #define rtc_H
    #define RTC_ADDRESS 0x68  // Dirección I2C del RTC DS1307/3231
    #define DS3231_TIME 0x00  // Dirección del registro 00h. Inicio de la memoria del RTC

    #include <Arduino.h>
    #include <Wire.h>

    typedef struct Data{
    byte second, minute, hour, dayOfWeek, dayOfMonth, month, year; 

    }DateTime;

    byte bcdToDec(byte bcd);

    byte decToBcd(byte fst, byte snd);

    int getDayOfWeek(int year, int month, int day);

    byte monthToBcd(String month);


    /*
     *  Con esta función comunicaremos desde donde queremos empezar
     *  a leer para posteriormente hacer una solicitud y obtener la 
     *  información de la fecha en formato de 24 horas
    */

    DateTime getTime(int rtc_addr, int regist_addr);

    byte* getCompDateTime(String time, String date);

    void setDateTime(byte* buffer);

    
#endif
