#include "rtcpoli.h"

byte bcdToDec(byte bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

byte decToBcd(byte fst, byte snd){
    return (fst << 4) | snd;
}

DateTime getTime(int rtc_addr){
    DateTime dateTime;

    Wire.beginTransmission(rtc_addr);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(rtc_addr, 7); //Pido 7 bytes, partiendo de 00h hasta 06h
    
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

int getDayOfWeek(int year, int month, int day){
    if (month < 3){
        month += 12;
        year--;
    }

    int h = (day + (13 * (month + 1) / 5) + year + (year / 4) - (year / 100) + (year / 400)) % 7;

    // Ajustar el resultado para que domingo sea 7
    return ((h + 6) % 7) + 1;
}

byte monthToBcd(String month){
    String months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", 
                       "Aug", "Sep", "Oct", "Nov", "Dec"}; 
    for(int i = 0; i < 12; i++){
        if(month == months[i]) return bcdToDec(i+1);
    }

    return -1;
}

void setDateTime(byte* buffer){
    Wire.beginTransmission(RTC_ADDRESS);
    Wire.write(buffer, 8);
    Wire.endTransmission();
}

byte* getCompDateTime(String time, String date){
    byte bcdSeconds = decToBcd((time[6] - '0'), time[7] - '0');
    byte bcdMinutes = decToBcd((time[3] - '0'), time[4] - '0');
    byte bcdHours = decToBcd((time[0] - '0'), time[1] - '0');

    String monthName;
    for(int i = 0; i<3; i++) monthName += date[i];

    byte bcdDayOfMonth = decToBcd((date[4] - '0'), date[5] - '0');
    byte bcdYear = decToBcd((date[9] - '0'), date[10] - '0');
    byte bcdMonth = monthToBcd(monthName); 
    byte bcdDayOfWeek = getDayOfWeek(bcdToDec(bcdYear) + 2000U, bcdToDec(bcdMonth), bcdToDec(bcdDayOfMonth));

    static byte buffer[8]= { DS3231_TIME,
                                bcdSeconds, 
                                bcdMinutes, 
                                bcdHours, 
                                bcdDayOfWeek, 
                                bcdDayOfMonth,
                                bcdMonth,
                                bcdYear
                            };

    Serial.println("Month Name: " + monthName);
    Serial.println("Month (decimal): " + String(bcdToDec(bcdMonth), DEC));
    Serial.println("");

    Serial.println("Year (decimal): " + String(bcdToDec(bcdYear), DEC));
    Serial.println("");

    Serial.println("Day of Week (binary): " + String(bcdDayOfWeek, BIN));
    Serial.println("Day of Week (decimal): " + String(bcdToDec(bcdDayOfWeek), DEC));

    Serial.println("");

    Serial.println("Day of Month (decimal): " + String(bcdToDec(bcdDayOfMonth), DEC));

    Serial.println("");

    Serial.println("Seconds (decimal): " + String(bcdToDec(bcdSeconds), DEC));
    Serial.println("Seconds (binary): " + String(bcdSeconds, BIN));

    Serial.println("");

    Serial.println("Minutes (decimal): " + String(bcdToDec(bcdMinutes), DEC));
    Serial.println("Minutes (binary): " + String(bcdMinutes, BIN));

    Serial.println("");

    Serial.println("Hours (decimal): " + String(bcdToDec(bcdHours), DEC));
    Serial.println("Hours (binary): " + String(bcdHours, BIN));
    
    return buffer;
}
