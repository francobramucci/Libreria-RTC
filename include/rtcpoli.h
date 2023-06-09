#ifndef rtc_H
    #define rtc_H
    #define RTC_ADDRESS 0x68  // Dirección I2C del RTC DS1307/3231


    #include <Arduino.h>
    #include <Wire.h>

    typedef struct Data{
    byte second, minute, hour, dayOfWeek, dayOfMonth, month, year; 

    }DateTime;


    byte bcdToDec(byte bcd);


    /*
     *  Con esta función comunicaremos desde donde queremos empezar
     *  a leer para posteriormente hacer una solicitud y obtener la 
     *  información de la fecha en formato de 24 horas
    */

    DateTime getTime(byte rtc_addr);
    
#endif
