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

//-----------------------------------------------------------
#include <DHT.h>
#define DHTPIN 12     // what digital pin we're connected to
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
                           0x5c,0x54,0x76,0x50,0x58};//n,h,H,r,c
*/
#define CLK 2//pins definitions for TM1637 and can be changed to other ports       
#define DIO 3
TM1637 tm1637(CLK, DIO);
DHT dht(DHTPIN, DHTTYPE);
int8_t NumTab[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
/*0~9,
   10 A,
   11 b,
   12 C,
   13 d,
   14 E,
   15 F,
   16 :,
   17 -,
   18 space,
   19 deg,
   20 o,
   21 n,
   22 H,
   23 r,
   24 c*/
int td = 10; //час в (затримка)
int timetoshift;
int P1, P2, P, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, P19, P20;//змінні для тискy
void setup() {
  pinMode(10, OUTPUT);//+5в
  pinMode(13, OUTPUT);//LED
  digitalWrite(10, HIGH);
  pinMode(5, OUTPUT);//PWM
  pinMode(4, INPUT_PULLUP);//кнопка режим1(показувати чи ні вологість на семисегмент)
  //
  tm1637.init();
  dht.begin();
  bme.begin();
  tm1637.set(7);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.display(0, NumTab[17]);
  delay(100);
  setSyncProvider(RTC.get);
  tm1637.display(1, NumTab[17]);
  delay(95);
  timetoshift = minute();
  P = round(round(bme.readPressure() / 10) / 10);
  P1 = P2 = P3 = P4 = P5 = P6 = P7 = P8 = P9 = P10 = P11 = P12 = P13 = P14 = P15 = P16 = P17 = P18 = P19 = P20 = P;
  tm1637.display(2, NumTab[17]);
  delay(100);
  tm1637.display(3, NumTab[17]);
  delay(100);
  tm1637.display(0, NumTab[18]);
  delay(100);
  tm1637.display(1, NumTab[18]);
  delay(100);
  tm1637.display(2, NumTab[18]);
  delay(100);
  tm1637.display(3, NumTab[18]);
  delay(100);

}
int b;
void loop() {
  int a, h, ho1, ho2, m1, m2;
  if (digitalRead(4) == 1) {

    if ((h = hour()) > 9) {
      ho1 = hour() / 10;
      ho2 = hour() % 10;
      m1 = minute() / 10;
      m2 = minute() % 10;
      tm1637.point(1);
      tm1637.display(0, NumTab[ho1]);
      tm1637.display(1, NumTab[ho2]);
      tm1637.display(2, NumTab[m1]);
      tm1637.display(3, NumTab[m2]);
    }
    else {
      ho2 = hour() % 10;
      m1 = minute() / 10;
      m2 = minute() % 10;
      tm1637.point(1);
      tm1637.display(0, NumTab[18]);
      tm1637.display(1, NumTab[ho2]);
      tm1637.display(2, NumTab[m1]);
      tm1637.display(3, NumTab[m2]);
    }
    delay(500);
    if ((h = hour()) > 9) {
      ho1 = hour() / 10;
      ho2 = hour() % 10;
      m1 = minute() / 10;
      m2 = minute() % 10;
      tm1637.point(0);
      tm1637.display(0, NumTab[ho1]);
      tm1637.display(1, NumTab[ho2]);
      tm1637.display(2, NumTab[m1]);
      tm1637.display(3, NumTab[m2]);
    }
    else {
      ho2 = hour() % 10;
      m1 = minute() / 10;
      m2 = minute() % 10;
      tm1637.point(0);
      tm1637.display(0, NumTab[18]);
      tm1637.display(1, NumTab[ho2]);
      tm1637.display(2, NumTab[m1]);
      tm1637.display(3, NumTab[m2]);
    }
    delay(500);
    if ((h = hour()) > 9) {
      ho1 = hour() / 10;
      ho2 = hour() % 10;
      m1 = minute() / 10;
      m2 = minute() % 10;
      tm1637.point(1);
      tm1637.display(0, NumTab[ho1]);
      tm1637.display(1, NumTab[ho2]);
      tm1637.display(2, NumTab[m1]);
      tm1637.display(3, NumTab[m2]);
    }
    else {
      ho2 = hour() % 10;
      m1 = minute() / 10;
      m2 = minute() % 10;
      tm1637.point(1);
      tm1637.display(0, NumTab[18]);
      tm1637.display(1, NumTab[ho2]);
      tm1637.display(2, NumTab[m1]);
      tm1637.display(3, NumTab[m2]);
    }

    int tz10 = (dht.readTemperature() * 10);
    pinMode(12, OUTPUT);
    delay(450);


    int tinz10 = (bme.readTemperature() - 4) * 10;// В ПРИМІЩЕННІ
    int zalyshoktinz10 = abs(tinz10) % 10;
    int tin = tinz10 / 10;
    tm1637.point(0);
    tm1637.clearDisplay();
    if (zalyshoktinz10 > 7) {
      tin++;
    }
    if (tin >= 10) {
      int t1 = tin / 10; //Відкидаю праву частину щоб вибрати номер з масиву.
      int t2 = tin % 10; //Відкидаю ліву частину -/-
      tm1637.display(0, NumTab[t1]);
      tm1637.display(1, NumTab[t2]);
      tm1637.display(2, NumTab[19]);//*
      tm1637.display(3, NumTab[24]);//c
    }
    if (tin < 10) {
      int t2 = tin % 10; //Відкидаю ліву частину -/-
      tm1637.display(0, NumTab[18]);
      tm1637.display(1, NumTab[t2]);
      tm1637.display(2, NumTab[19]);
      tm1637.display(3, NumTab[12]);
    }

    delay(1500);
    // Wait a few seconds between measurements.
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    // Read temperature as Celsius (the default)

    int zalyshoktz10 = abs(tz10) % 10;
    int t = tz10 / 10;
    tm1637.clearDisplay();
    if (t >= 0) {
      if (zalyshoktz10 >= 5) {
        t++;
      }
      if (t >= 10) {
        int t1 = t / 10; //Відкидаю праву частину щоб вибрати номер з масиву.
        int t2 = t % 10; //Відкидаю ліву частину -/-
        tm1637.display(0, NumTab[t1]);
        tm1637.display(1, NumTab[t2]);
        tm1637.display(2, NumTab[19]);
        tm1637.display(3, NumTab[12]);
      }
      if ((t < 10)&&(t>=0)) {
        int t2 = t % 10; //Відкидаю ліву частину -/-
        tm1637.display(0, NumTab[18]);
        tm1637.display(1, NumTab[t2]);
        tm1637.display(2, NumTab[19]);
        tm1637.display(3, NumTab[12]);
      }
    }
    if (t < 0) {
      if (zalyshoktz10 >= 5) {
        t--;
      }
      
      if (t >-10) {
        t = abs(t);//не заплутатись з мінусом далі йдуть додатні температури.
        int t2 = t % 10;
        tm1637.display(0, NumTab[17]);//-
        tm1637.display(1, NumTab[t2]);
        tm1637.display(2, NumTab[19]);
        tm1637.display(3, NumTab[12]);
      }
      if (t < -9) {
        t = abs(t);//не заплутатись з мінусом далі йдуть додатні температури.
        int t1 = t / 10; //Відкидаю праву частину щоб вибрати номер з масиву.
        int t2 = t % 10; //Відкидаю ліву частину -/-
        tm1637.display(0, NumTab[17]);//-
        tm1637.display(1, NumTab[t1]);
        tm1637.display(2, NumTab[t2]);
        tm1637.display(3, NumTab[19]);//*
      }
    }
    delay(1500);

    P = round(round(bme.readPressure() / 10) / 10); //тупо читаємо дані тиску
    int det = minute() - timetoshift; //різниця між реальним часом і старим цикловим
    if ((det >= td) || (det < 0)) //умова розподілу за різницею в часі
    {
      timetoshift = minute(); //////тут змінюємо місцями тиски і прирівнюємо старий новий час
      P10 = P20;
      P20 = P19;
      P19 = P18;
      P18 = P17;
      P17 = P16;
      P16 = P15;
      P15 = P14;
      P14 = P13;
      P13 = P12;
      P12 = P11;
      P11 = P9;
      P9 = P8;
      P8 = P7;
      P7 = P6;
      P6 = P5;
      P5 = P4;
      P4 = P3;
      P3 = P2;
      P2 = P1;
      P1 = P;
    }

    if (P10 == P11 && P10 == P) {
      printpress();
      delay(1250);
    }
    if (P10 != P || P11 != P) {
      tm1637.clearDisplay();
      delay(200);
      tm1637.set(3);
      printpress1();
      delay(1000);
      tm1637.clearDisplay();
      delay(200);
      tm1637.set(5);
      printpress2();
      delay(1000);
      tm1637.clearDisplay();
      delay(200);
      tm1637.set(7);
      printpress();
      delay(1100);

    }

    int hz10 = (dht.readHumidity() * 10);
    int zalyshokhz10 = hz10 % 10;
    int h = hz10 / 10;
    // Serial.println(hz10);/////
    if (zalyshokhz10 > 5) { ///////////////////////12,5=13
      h++;
    }
    analogWrite(5, 0);
    if (h <= 15)
      a = 0;
    else if (h >= 16 && h <= 19)
      a = 3;
    else if (h >= 20 && h <= 21)
      a = 4;
    else if (h >= 22 && h <= 25)
      a = 5;
    else if (h >= 26 && h <= 29)
      a = 6;
    else if (h >= 30 && h <= 33)
      a = 7;
    else if (h >= 34 && h <= 35)
      a = 8;
    else if (h >= 36 && h <= 39)
      a = 9;
    else if (h >= 40 && h <= 43)
      a = 10;
    else if (h >= 44 && h <= 45)
      a = 11;
    else if (h >= 46 && h <= 49)
      a = 12;
    else if (h >= 50 && h <= 53)
      a = 13;
    else if (h >= 54 && h <= 55)
      a = 14;
    else if (h >= 56 && h <= 58)
      a = 15;
    else if (h >= 59 && h <= 61)
      a = 15;
    else if (h >= 62 && h <= 64)
      a = 16;
    else if (h >= 65 && h <= 68)
      a = 17;
    else if (h >= 69 && h <= 71)
      a = 18;
    else if (h >= 72 && h <= 74)
      a = 19;
    else if (h >= 75 && h <= 77)
      a = 20;
    else if (h >= 78 && h <= 79)
      a = 21;
    else if (h >= 80 && h <= 83)
      a = 22;
    else if (h >= 84 && h <= 86)
      a = 23;
    else if (h >= 87 && h <= 89)
      a = 23;
    else if (h >= 90 && h <= 93)
      a = 24;
    else if (h >= 94 && h <= 95)
      a = 24;
    else if (h >= 96 && h <= 98)
      a = 25;
    else if (h >= 99 && h <= 100)
      a = 26;
    else if (h >= 101)
      a = 27;
    analogWrite(5, a);
  }
  ///
  ///
  ///
  ///
  ///ДРУГА ФУНКЦІЯ ЗНИЗУ
  ///
  ///
  ///
  ///
  else {
    pinMode(5, INPUT);
    pinMode(5, OUTPUT);
    tm1637.point(0);
    int hz10 = (dht.readHumidity() * 10);
    int zalyshokhz10 = hz10 % 10;
    int h = hz10 / 10;
    if (zalyshokhz10 > 5) {
      h++;
    }
    analogWrite(5, 0);

    int h1 = h / 10;
    int h2 = h % 10;
    tm1637.display(0, NumTab[h1]);
    tm1637.display(1, NumTab[h2]);
    tm1637.display(2, NumTab[19]);
    tm1637.display(3, NumTab[20]);
    delay(2000);
  }
}


void printpress1() {
  int p = P10;
  int p1, p2, p3, p4;
  if (p >= 1000) {
    p1 = p / 1000;
    p2 = (p / 100) % 10;
    p3 = (p % 100) / 10;
    p4 = p % 10;
    tm1637.display(0, NumTab[p1]);
    tm1637.display(1, NumTab[p2]);
    tm1637.display(2, NumTab[p3]);
    tm1637.display(3, NumTab[p4]);
  }
  if (p < 1000) {
    p1 = p / 1000;
    p2 = (p / 100) % 10;
    p3 = (p % 100) / 10;
    p4 = p % 10;
    tm1637.display(0, NumTab[18]);
    tm1637.display(1, NumTab[p2]);
    tm1637.display(2, NumTab[p3]);
    tm1637.display(3, NumTab[p4]);
  }
}
//
void printpress2() {
  int p = P11;
  int p1, p2, p3, p4;
  if (p >= 1000) {
    p1 = p / 1000;
    p2 = (p / 100) % 10;
    p3 = (p % 100) / 10;
    p4 = p % 10;
    tm1637.display(0, NumTab[p1]);
    tm1637.display(1, NumTab[p2]);
    tm1637.display(2, NumTab[p3]);
    tm1637.display(3, NumTab[p4]);
  }
  if (p < 1000) {
    p1 = p / 1000;
    p2 = (p / 100) % 10;
    p3 = (p % 100) / 10;
    p4 = p % 10;
    tm1637.display(0, NumTab[18]);
    tm1637.display(1, NumTab[p2]);
    tm1637.display(2, NumTab[p3]);
    tm1637.display(3, NumTab[p4]);
  }
}
//
void printpress() {
  int p = P;
  int p1, p2, p3, p4;
  if (p >= 1000) {
    p1 = p / 1000;
    p2 = (p / 100) % 10;
    p3 = (p % 100) / 10;
    p4 = p % 10;
    tm1637.display(0, NumTab[p1]);
    tm1637.display(1, NumTab[p2]);
    tm1637.display(2, NumTab[p3]);
    tm1637.display(3, NumTab[p4]);
  }
  if (p < 1000) {
    p1 = p / 1000;
    p2 = (p / 100) % 10;
    p3 = (p % 100) / 10;
    p4 = p % 10;
    tm1637.display(0, NumTab[18]);
    tm1637.display(1, NumTab[p2]);
    tm1637.display(2, NumTab[p3]);
    tm1637.display(3, NumTab[p4]);
  }
}
