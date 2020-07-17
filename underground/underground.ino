// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
#include <EEPROM.h>
#include <Wire.h>
#include "TM1637.h"
#include <SPI.h>
#include "DHT.h"
#define CLK 2//pins definitions for TM1637 and can be changed to other ports       
#define DIO 3
TM1637 tm1637(CLK, DIO);
#define DHTTYPE DHT22
DHT dht1(6, DHT22);
DHT dht2(7, DHT22);
int8_t NumTab[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};
/*0~9,
   10 A,
   11 b,
   12 C,
   13 d,
   14 E,
   15 F,
   16 P,
   17 -,
   18 space,
   19 deg,
   20 o,
   21 n,
   22 H,
   23 r,
   24 c
   25 _
   26 -
   27 -t
   28 -rd
   29 -lt
   30 -rt
   31 -ld
   32 П
   33 І
   34 h
   35 t
   36 G*/
//************Button*****************//
int P1 = 11; // Button SET MENU'
int P2 = 9; // Button +
int P3 = 10; // Button -

//************Variables**************//
int rel1 = 13;
//int rel2 = 12;
int temperature = 1;
int humid = 91;
int dt = 1;
int dh = 1;
int menu = 0;
int ONOFF = 0;
int animon = 0;
int anihum = 0;
void setup()
{
  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);
  pinMode(rel1, OUTPUT);
  //pinMode(rel2, OUTPUT);
  // Serial.begin(9600);
  dht1.begin();
  dht2.begin();
  tm1637.init();
  /* EEPROM.get(0, temperature);
    EEPROM.get(1, dt);
    EEPROM.get(2, humid);
    EEPROM.get(3, dh);*/
  /*EEPROM.put(0, temperature);
      EEPROM.put(10, dt);
      EEPROM.put(20, humid);
      EEPROM.put(30, dh);*/
  EEPROM.get(0, temperature);
  EEPROM.get(10, dt);
  EEPROM.get(20, humid);
  EEPROM.get(30, dh);
  //hi();


tm1637.set(4);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.display(0, NumTab[25]);
  delay(50);
  tm1637.display(0, NumTab[18]);
  delay(50);
  tm1637.display(0, NumTab[25]);
  tm1637.display(1, NumTab[25]);
  delay(100);
  tm1637.display(1, NumTab[18]);
  delay(50);
  tm1637.display(1, NumTab[25]);
  tm1637.display(2, NumTab[25]);
  delay(100);
  tm1637.display(2, NumTab[18]);
  delay(50);
  tm1637.display(2, NumTab[25]);
  tm1637.display(3, NumTab[25]);
  delay(100);
  tm1637.display(3, NumTab[18]);
  delay(50);
  tm1637.display(3, NumTab[25]);
  delay(200);
  tm1637.clearDisplay();
  delay(10);
  tm1637.set(7);
  tm1637.display(0, NumTab[27]);
  tm1637.display(1, NumTab[27]);
  tm1637.display(2, NumTab[27]);
  tm1637.display(3, NumTab[27]);
  delay(20);
  tm1637.clearDisplay();

  
  tm1637.set(2);// СТАВИМО ЯСКРАВІСТЬ ТАКУ, ЯКУ ХОЧЕМО
}

void DisplayTempHum ()
{
  float h1 = dht1.readHumidity(); //двір
  float t1 = dht1.readTemperature();
  float h2 = dht2.readHumidity();//хата
  float t2 = dht2.readTemperature();
  if (digitalRead(P1) == HIGH)
  { ////////
    if (t2 > temperature)
    {
      if ((t2 - t1) >= dt + 0.5)
      {
        if (t2 >= temperature + 0.5)digitalWrite(rel1, HIGH);
      }
      if ((t2 - t1) <= dt - 0.5) digitalWrite(rel1, LOW);
    }
    else digitalWrite(rel1, LOW);
  }
  ////////
  else
  {
    digitalWrite(rel1, LOW);
  }
  //t1z10*************+++++


  int t1z10 = (t1 * 10);
  int zalyshokt1z10 = abs(t1z10) % 10;
  int t = t1z10 / 10;
  if (t >= 0) {
    if (zalyshokt1z10 >= 6) {
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
    if ((t < 10) && (t >= 0)) {
      int t2 = t % 10; //Відкидаю ліву частину -/-
      tm1637.display(0, NumTab[18]);
      tm1637.display(1, NumTab[t2]);
      tm1637.display(2, NumTab[19]);
      tm1637.display(3, NumTab[12]);
    }
  }
  if (t < 0) {
    if (zalyshokt1z10 >= 6) {
      t--;
    }
    t = abs(t);
    if (t > -10) {
      int t2 = t % 10;
      tm1637.display(0, NumTab[17]);//-
      tm1637.display(1, NumTab[t2]);
      tm1637.display(2, NumTab[19]);
      tm1637.display(3, NumTab[12]);
    }
    if (t <= -10) {
      int t1 = t / 10;
      int t2 = t % 10;
      tm1637.display(0, NumTab[17]);//-
      tm1637.display(1, NumTab[t1]);
      tm1637.display(2, NumTab[t2]);
      tm1637.display(3, NumTab[19]);//*
    }
  }
  delay(1500);

if (digitalRead(P1) == HIGH)
{
  int h1z10 = (h1 * 10);
  int zalyshokh1z10 = h1z10 % 10;
  int h = h1z10 / 10;

  if (zalyshokh1z10 > 5) {
    h++;
  }
  if (h >= 100) {
    h = 99;
  }

  int hh1 = h / 10;
  int hh2 = h % 10;
  tm1637.display(0, NumTab[hh1]);
  tm1637.display(1, NumTab[hh2]);
  tm1637.display(2, NumTab[19]);
  tm1637.display(3, NumTab[20]);
  delay(1500);
}
//t1z10*********----------------------

if (digitalRead(P1) == HIGH)
{
  int t2z10 = (t2 * 10);
  //t2z10*****
  int zalyshokt2z10 = abs(t2z10) % 10;
  int    t = t2z10 / 10;
  if (t >= 0) {
    if (zalyshokt2z10 >= 6) {
      t++;
    }
    if (t >= 10) {
      int t1 = t / 10; //Відкидаю праву частину щоб вибрати номер з масиву.
      int t2 = t % 10; //Відкидаю ліву частину -/-
      tm1637.display(0, NumTab[t1]);
      tm1637.display(1, NumTab[t2]);
      tm1637.display(2, NumTab[19]);
      tm1637.display(3, NumTab[24]);
    }
    if ((t < 10) && (t >= 0)) {
      int t2 = t % 10; //Відкидаю ліву частину -/-
      tm1637.display(0, NumTab[18]);
      tm1637.display(1, NumTab[t2]);
      tm1637.display(2, NumTab[19]);
      tm1637.display(3, NumTab[24]);
    }
  }
  if (t < 0) {
    if (zalyshokt2z10 >= 6) {
      t--;
    }
    t = abs(t);
    if (t > -10) {
      int t2 = t % 10;
      tm1637.display(0, NumTab[17]);//-
      tm1637.display(1, NumTab[t2]);
      tm1637.display(2, NumTab[19]);
      tm1637.display(3, NumTab[24]);
    }
    if (t <= -10) {
      int t1 = t / 10;
      int t2 = t % 10;
      tm1637.display(0, NumTab[17]);//-
      tm1637.display(1, NumTab[t1]);
      tm1637.display(2, NumTab[t2]);
      tm1637.display(3, NumTab[24]);//*
    }
  }
  delay(1500);
}
if (digitalRead(P1) == HIGH)
{
  //tz10******
  ////////////// //////////////////////////////////////////////////
  //hz10******
  int h2z10 = (h2 * 10);
  int zalyshokh2z10 = h2z10 % 10;
  int h = h2z10 / 10;
  if (zalyshokh2z10 > 5) {
    h++;
  }
  if (h >= 100) {
    h = 99;
  }
  int   hh1 = h / 10;
  int   hh2 = h % 10;
  tm1637.display(0, NumTab[hh1]);
  tm1637.display(1, NumTab[hh2]);
  tm1637.display(2, NumTab[19]);
  tm1637.display(3, NumTab[20]);
  delay(600);
  //hz10******
}
}

void SetTemp()
{
  //Встановлює температуру, до якої працювати
  if (digitalRead(P2) == LOW)
  {
    if (temperature == 35)
    {
      temperature = -9;
    }
    else
    {
      temperature++;

    }

  }
  if (digitalRead(P3) == LOW)
  {
    if (temperature == -9)
    {
      temperature = 35;
    }
    else
    {
      temperature--;

    }
  }
  int  t = temperature;
  if (t >= 10) {
    int t1 = t / 10; //Відкидаю праву частину щоб вибрати номер з масиву.
    int t2 = t % 10; //Відкидаю ліву частину -/-
    tm1637.display(0, NumTab[35]);
    tm1637.display(1, NumTab[18]);
    tm1637.display(2, NumTab[t1]);
    tm1637.display(3, NumTab[t2]);
  }
  if ((t < 10) && (t >= 0)) {
    int t2 = t % 10; //Відкидаю ліву частину -/-
    tm1637.display(0, NumTab[35]);
    tm1637.display(1, NumTab[18]);
    tm1637.display(2, NumTab[18]);
    tm1637.display(3, NumTab[t2]);
  }
  if (t < 0) {
    t = abs(t);
    if (t > -10) {
      int t2 = t % 10;
      tm1637.display(0, NumTab[35]);//-
      tm1637.display(1, NumTab[18]);
      tm1637.display(2, NumTab[17]);
      tm1637.display(3, NumTab[t2]);
    }
    if (t <= -10) {
      int t1 = t / 10;
      int t2 = t % 10;
      tm1637.display(0, NumTab[35]);//-
      tm1637.display(1, NumTab[17]);
      tm1637.display(2, NumTab[t1]);
      tm1637.display(3, NumTab[t2]);//*
    }
  }

  if ((digitalRead(P2) == LOW) || (digitalRead(P3) == LOW)) {
    delay(100);
  }
}

void Setdt()
{
  // Setting the minutes
  //  tm1637.clearDisplay();
  if (digitalRead(P2) == LOW)
  {
    if (dt == 15)
    {
      dt = 1;
    }
    else
    {
      dt++;

    }
  }
  if (digitalRead(P3) == LOW)
  {
    if (dt == 1)
    {
      dt = 15;
    }
    else
    {
      dt--;

    }
  }
  int t2 = dt % 10; //Відкидаю ліву частину -/-
  int t1 = dt / 10;
  if (t1 <= 0) {
    t1 = 18;
  }
  tm1637.display(0, NumTab[13]);
  tm1637.display(1, NumTab[35]);
  tm1637.display(2, NumTab[t1]);
  tm1637.display(3, NumTab[t2]);
  if ((digitalRead(P2) == LOW) || (digitalRead(P3) == LOW)) {
    delay(100);
  }
  //delay(100);
}

void SetHum()
{
  // tm1637.clearDisplay();
  if (digitalRead(P2) == LOW)
  {
    if (humid == 99)
    {
      humid = 20;
    }
    else
    {
      humid++;

    }
  }
  if (digitalRead(P3) == LOW)
  {
    if (humid == 20)
    {
      humid = 99;
    }
    else
    {
      humid--;

    }
  }

  int h1 = humid / 10;
  int h2 = humid % 10;
  if (h1 <= 0) {
    h1 = 18;
  }
  tm1637.display(0, NumTab[34]);
  tm1637.display(1, NumTab[18]);
  tm1637.display(2, NumTab[h1]);
  tm1637.display(3, NumTab[h2]);
  if ((digitalRead(P2) == LOW) || (digitalRead(P3) == LOW)) {
    delay(100);
  }
  // delay(100);
}

void Setdh()
{
  // Setting the month
  //3 tm1637.clearDisplay();
  if (digitalRead(P2) == LOW)
  {
    if (dh == 55)
    {
      dh = 0;
    }
    else
    {
      dh++;

    }
  }
  if (digitalRead(P3) == LOW)
  {
    if (dh == 0)
    {
      dh = 55;
    }
    else
    {
      dh--;

    }
  }

  int h1 = dh / 10;
  int h2 = dh % 10;
  if (h1 <= 0) {
    h1 = 18;
  }
  tm1637.display(0, NumTab[13]);
  tm1637.display(1, NumTab[34]);
  tm1637.display(2, NumTab[h1]);
  tm1637.display(3, NumTab[h2]);
  if ((digitalRead(P2) == LOW) || (digitalRead(P3) == LOW)) {
    delay(100);
  }
}

void SetOnOff()
{
  if (digitalRead(P2) == LOW)
  {
    if (ONOFF == 1)
    {
      ONOFF = 0;
    }
    else
    {
      ONOFF++;

    }
  }
  if (digitalRead(P3) == LOW)
  {
    if (ONOFF == 0)
    {
      ONOFF = 1;
    }
    else
    {
      ONOFF--;

    }
  }
  if (ONOFF == 1) {
    if (animon == 0) {
      digitalWrite(rel1, HIGH);
      tm1637.display(0, NumTab[27]);
      tm1637.display(1, NumTab[18]);
      tm1637.display(2, NumTab[0]);
      tm1637.display(3, NumTab[32]);
    }
    if (animon == 1) {
      tm1637.display(0, NumTab[18]);
      tm1637.display(1, NumTab[27]);
      tm1637.display(2, NumTab[0]);
      tm1637.display(3, NumTab[32]);
      animon = -1;
    }
    animon++;
    delay(100);
    if ((digitalRead(P2) == LOW) || (digitalRead(P3) == LOW)) {
      delay(50);
    }
  }
  else {
    digitalWrite(rel1, LOW);
    tm1637.display(0, NumTab[25]);
    tm1637.display(1, NumTab[0]);
    tm1637.display(2, NumTab[15]);
    tm1637.display(3, NumTab[15]);
    if ((digitalRead(P2) == LOW) || (digitalRead(P3) == LOW)) {
      delay(150);
    }
  }
}
void loop()
{

  if (digitalRead(P1) == LOW)
  {
    if (menu == 0) {
      tm1637.clearDisplay();
      delay(500);
    }
    menu++;
    delay(200);
    if (digitalRead(P1) == LOW)  {
      delay(200);
      if (digitalRead(P1) == LOW)  {
        menu++;
        delay(300);
        if (digitalRead(P1) == LOW) {
          menu--;
        }
      }

    }
  }
  // in which subroutine should we go?
  if (menu == 0)
  {
    if (digitalRead(P1) == LOW) {
      tm1637.clearDisplay();
      delay(500);
    }
    DisplayTempHum();
  }
  if (menu == 1)
  {
    digitalWrite(rel1, LOW);
    ONOFF = 0;
    SetTemp();
  }

  if (menu == 2)
  {
    Setdt();
  }
  if (menu == 3)
  {
    SetHum();
  }
  if (menu == 4)
  {
    /* tm1637.display(0, NumTab[18]);
      tm1637.display(1, NumTab[18]);
      delay(30);*/
    Setdh();
    //delay(100);
  }
  if (menu == 5)
  {
    SetOnOff();
    // delay(100);
  }
  if (menu >= 6)
  {
    EEPROM.put(0, temperature);
    EEPROM.put(10, dt);
    EEPROM.put(20, humid);
    EEPROM.put(30, dh);

    tm1637.display(0, NumTab[36]);
    tm1637.display(1, NumTab[20]);
    tm1637.display(2, NumTab[20]);
    tm1637.display(3, NumTab[13]);
    menu = 0;
    delay(500);
  }
  // delay(300);
}

