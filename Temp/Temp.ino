#include <UTFT.h>
#include<OneWire.h>
#include<DallasTemperature.h>
#include <Wire.h>
#include <DS1302.h>

#define ONE_WIRE_BUS 5
extern uint8_t SmallFont[];

UTFT LCD(15,A2,A1,A5,A4,A3);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

DS1302 rtc(2, 3, 4); // RST, DAT, CLK
void setup(){

  LCD.InitLCD(PORTRAIT);
  LCD.setFont(SmallFont);

  Serial.begin(9600);
  sensors.begin();
  
  rtc.halt(false);
  rtc.writeProtect(false);
 
  // to be commented
  //setCurrentTime();
  
  startUp();
}

// set Time
void setCurrentTime(){
  
  rtc.setDOW(SATURDAY);
  rtc.setTime(23, 40, 00);
  rtc.setDate(15, 8, 2020);
 // rtc.writeProtect(true);
  
}
// begin splash
void startUp(){
  
  LCD.clrScr();
  LCD.setBackColor(22, 97, 171);
  LCD.setColor(255,255,255);
  LCD.print("Have A Good Day", CENTER, CENTER+50);
  delay(1500);
  LCD.clrScr();
  LCD.setColor(238, 44,121);
  LCD.drawRoundRect(0,0,127,127);
  
  LCD.setBackColor(0,0,0);
}

// get temperature
void getTemperatureNow(){
  
   sensors.requestTemperatures(); 
  float temp = sensors.getTempCByIndex(0);
//  char c[6];
//  dtostrf(temp,3,2,c);

  LCD.setColor(255,255,0);
  LCD.print("Temp: " ,10,10);
  LCD.setColor(255,63,36);
//  LCD.print(c,60,11);
 LCD.printNumF(temp,2,60,11);
 
}

// get time
void getTimeNow(){
  
  LCD.setColor(0,255,0); 
  LCD.print("Date: ",10,25);
  LCD.setColor(255,63,36);
  LCD.print(rtc.getDateStr(FORMAT_LONG, FORMAT_BIGENDIAN, '/'),10,40);

  LCD.setColor(0,0,255);
  LCD.print("Week: ",10,55);
  LCD.setColor(255,63,36);
  LCD.print(rtc.getDOWStr(),10,70);
  
  
  LCD.setColor(255,192,203);
  LCD.print("Time: ",10,85);
  LCD.setColor(255,63,36);
  LCD.print(rtc.getTimeStr(),10,100);
  
  Serial.println(rtc.getTimeStr());
  
}


void loop(){
  
  getTemperatureNow();
  getTimeNow();
  
//  delay(1000);
}

