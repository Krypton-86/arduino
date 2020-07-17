#include <Wire.h>
#include <SPI.h>
#include <Time.h>
#include <DS1307RTC.h>
////////////////////////////
#include <Adafruit_BMP280.h>

#define BMP_SCK 9  //SCK
#define BMP_MISO 8 //SDO
#define BMP_MOSI 7 //SDI
#define BMP_CS 6   //CS

Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);
#include <DHT.h>
#define DHTPIN 5     // what digital pin we're connected to
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
//----------------------------------------------------------------------------
#include "TM1637.h"
/*Додати в TM1637.cpp      
static int8_t TubeTab[] = {0x3f,0x06,0x5b,0x4f,
                           0x66,0x6d,0x7d,0x07,
                           0x7f,0x6f,0x77,0x7c,
                           0x39,0x5e,0x79,0x71,//0~9,A,b,C,d,E,F
                           0x80,0x40,0x00,0x63,//:,-,space,deg
                           0x5c,0x54,0x76,0x50};//n,h,H,r                        
*/
#define CLK 2//pins definitions for TM1637 and can be changed to other ports       
#define DIO 3
TM1637 tm1637(CLK,DIO);
DHT dht(DHTPIN, DHTTYPE);
int8_t NumTab[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
                /*0~9,
                 * 10 A,
                 * 11 b,
                 * 12 C,
                 * 13 d,
                 * 14 E,
                 * 15 F,
                 * 16 :,
                 * 17 -,
                 * 18 space,
                 * 19 deg,
                 * 20 o,
                 * 21 n,
                 * 22 H,
                 * 23 r*/

void setup() {
     dht.begin();
  pinMode(13, OUTPUT);//LED
  pinMode(12, OUTPUT);//PWM
   pinMode(10, OUTPUT);//+5
   digitalWrite(10, HIGH);
  tm1637.init();
  if (!bme.begin()) {  
    digitalWrite(13, HIGH);
    while (1);
  tm1637.set(6);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  
  tm1637.display(0,NumTab[17]);
  delay(200);
  tm1637.display(1,NumTab[17]);
  delay(200);
  tm1637.display(2,NumTab[17]);
  delay(200);
  tm1637.display(3,NumTab[17]);
  delay(200);
  tm1637.display(0,NumTab[18]);
  delay(200);
  tm1637.display(1,NumTab[18]);
  delay(200);
  tm1637.display(2,NumTab[18]);
  delay(200);
  tm1637.display(3,NumTab[18]);
  delay(200);
  digitalWrite(13, HIGH);
  delay(50);
  digitalWrite(13, LOW);
  delay(20);
  digitalWrite(13, HIGH);
  delay(70);
  digitalWrite(13, LOW);
  delay(30);
  digitalWrite(13, HIGH);
  delay(10);
  digitalWrite(13, LOW);
  delay(20);
  digitalWrite(13, HIGH);
  delay(50);
  digitalWrite(13, LOW);
  delay(10);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(20);
     }
int b;
void loop() {
 
  if (digitalRead(8)==1){
    pinMode(6, OUTPUT);
  // tm1637.point(1);
  // Wait a few seconds between measurements.
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int hz10=(dht.readHumidity()*10);
  int zalyshokhz10=hz10%10;
  int h=hz10/10;
// Serial.println(hz10);/////
  if(zalyshokhz10>5){
    h++;}
//  Serial.println(h);/////
  int a=digitalRead(9);
        if (h>=65){
        digitalWrite(13, HIGH);
        digitalWrite(11, LOW);}
       else {    
        digitalWrite(13, LOW);      
        digitalWrite(11, HIGH);}
         if(a==1)
         {b=10;}/////////////////////////////////////////////////////////1/3 числa секунд вкл. витяжки(треба 60 сек -> пиши 20)
        if(b>0){
    digitalWrite(13, HIGH);
    digitalWrite(11, LOW);
    b--;}
    
////////////////////////////////
///////////////////////////////
//////////////////////////////
if (h<=15)
  a=0;
  else if (h>=16&&h<=19)
  a=1;
  else if (h>=20&&h<=21)
  a=2;
  else if (h>=22&&h<=25)
  a=3;
  else if (h>=26&&h<=29)
  a=4;
  else if (h>=30&&h<=33)
  a=5;
  else if (h>=34&&h<=35)
  a=6;
  else if (h>=36&&h<=39)
  a=7;
  else if (h>=40&&h<=43)
  a=8;
  else if (h>=44&&h<=45)
  a=9;
  else if (h>=46&&h<=49)
  a=10;
  else if (h>=50&&h<=53)
  a=11;
  else if (h>=54&&h<=55)
  a=12;
  else if (h>=56&&h<=58)
  a=13;
  else if (h>=59&&h<=61)
  a=14;
  else if (h>=62&&h<=64)
  a=15;
  else if (h>=65&&h<=68)
  a=16;
  else if (h>=69&&h<=71)
  a=17;
  else if (h>=72&&h<=74)
  a=18;
  else if (h>=75&&h<=77)
  a=19;
  else if (h>=78&&h<=79)
  a=20;
  else if (h>=80&&h<=83)
  a=21;
  else if (h>=84&&h<=86)
  a=22;
  else if (h>=87&&h<=89)
  a=23;
  else if (h>=90&&h<=93)
  a=24;
  else if (h>=94&&h<=95)
  a=25;
  else if (h>=96&&h<=98)
  a=26;
  else if (h>=99&&h<=100)
  a=27;
  else if (h>=101)
  a=28;
analogWrite(6, a);
/////////////////////////////////
////////////////////////////////
/////////////////////////////// 
  int h1=h/10;
  int h2=h%10;
  tm1637.clearDisplay();
  tm1637.display(0,NumTab[h1]);
  tm1637.display(1,NumTab[h2]);
  tm1637.display(2,NumTab[18]);
  tm1637.display(3,NumTab[11]);
  delay(2000);
  // Read temperature as Celsius (the default)
   
  
  int tz10=(dht.readTemperature()*10);
  int zalyshoktz10=tz10%10;
  int t=tz10/10;
//  Serial.println(tz10);/////
  if(zalyshoktz10>5){
    t++;}
//  Serial.println(t);
  tm1637.clearDisplay();
  if (t>=0){
    if(t>=10){
  int t1 = t/10;//Відкидаю праву частину щоб вибрати номер з масиву.
  int t2 = t%10;//Відкидаю ліву частину -/-
  tm1637.display(0, NumTab[t1]);
  tm1637.display(1, NumTab[t2]);
  tm1637.display(2, NumTab[19]);
  tm1637.display(3, NumTab[12]);
  }
    if(t<10){
  int t2 = t%10;//Відкидаю ліву частину -/-
  tm1637.display(0, NumTab[18]);
  tm1637.display(1, NumTab[t2]);
  tm1637.display(2, NumTab[19]);
  tm1637.display(3, NumTab[12]);      
    }}
  else if(t<0){
    if(t>-10){  
  int t2 = t%10;
  tm1637.display(0, NumTab[17]);
  tm1637.display(1, NumTab[t2]);
  tm1637.display(2, NumTab[19]);
  tm1637.display(3, NumTab[12]);
    } 
    if(t<=-10){
  int t1 = t/10;
  int t2 = t%10;
  tm1637.display(0, NumTab[17]);
  tm1637.display(1, NumTab[t1]);
  tm1637.display(2, NumTab[t2]);
  tm1637.display(3, NumTab[12]);
  }} 
  delay(2000);}
  else{
    tm1637.clearDisplay();
    pinMode(6, INPUT);
       }
  }
