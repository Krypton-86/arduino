#include <Wire.h>
#include <SPI.h>
#include "TM1637.h"
#define CLK 13//pins definitions for TM1637 and can be changed to other ports       
#define DIO 12
TM1637 tm1637(CLK,DIO);
int dtime=50;
/*0~9,  A,  b,  C,  d,  E,  F,  P,  -, space, deg,  o,  n,  H, r,  c,   _,  -, -top-,  r_, lt, rt, l_,  П,  І,   
  0-9, 10, 11, 12, 13, 14, 15, 16, 17,    18,  19, 20, 21, 22, 23, 24, 25, 26,    27,  28, 29, 30, 31, 32, 33, 34              
*/

int FINE[] = {15, 33, 32, 14};//FINE
int CLRSCR[]={18, 18, 18, 18};//стерти


void print_disp(int x[]) {    //функця для удобной работы с дисплеем (на вход полаётся массив из 4 чисел, они выводятся на дисплей)
  for (int i = 0; i <= 3; i++) {tm1637.display(i, x[i]); delay(dtime);}} 
void print_clr() {    //функцiя почергового стирання
  for (int i = 0; i <= 3; i++) {tm1637.display(i, 18);delay(dtime);}} 
              
void setup() {
pinMode(10, OUTPUT);//+5в
pinMode(11, OUTPUT);//0
digitalWrite(10, HIGH);
digitalWrite(11, LOW);
///////////////////////////////

///////////////////////////////

tm1637.init();
tm1637.set(2);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}

void loop() {

 print_disp(FINE);
  delay(dtime*50);
  print_clr();
 
}
