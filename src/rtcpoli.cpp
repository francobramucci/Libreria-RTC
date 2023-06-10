#include "rtcpoli.h"

byte bcdToDec(byte bcd) {
  return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

DateTime getTime(int rtc_addr){
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


