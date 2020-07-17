//promini 3.3 8mhz
//!!!
#include <SoftwareSerial.h>                 // if software serial
SoftwareSerial gsm(7, 8); // RX, TX
//#define gsm Serial                           //if hardware in UNO
//#define gsm Serial1                          // if hardware in Leonardo

#define LED 3
int brigh=5;

#define T1 "0999999999"                // !! phone numbers
#define T2 "0988888888"
#define T3 "0687777777"

#define r1 9                             // !! relay pin
#define r2 11
#define key 10

#define pinBOOT 5                            // pin BOOT or K on gsm module M590
/////////////////////////
void setup() {
  delay(1000);                              //// !! to avoid bootloop

  gsm.begin(9600);                           /// UART speed
  //Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(pinBOOT, OUTPUT);                 
  pinMode(r1, OUTPUT);                    
  pinMode(r2, OUTPUT);
  digitalWrite(r2, HIGH);
  pinMode(key, INPUT_PULLUP);
  delay(1000);
  analogWrite(LED, brigh);                   //  turn on LED
  ///// включаем модем,
  gsm.println("AT");                         //  command to check connect
  delay(100);
  if (!gsm.find("OK")) {                     // if fail then reset module
    digitalWrite(pinBOOT, LOW);
    delay(1000);
    digitalWrite(pinBOOT, HIGH);
  }
  // waiting connection to the cell network
  delay(2000);

  gsm.println("ATE0");                  // disconnecting echo

  while (1) {                           
    gsm.println("AT+COPS?");
    if (gsm.find("+COPS: 0")) break;
    analogWrite(LED, brigh);               
    delay(50);
    analogWrite(LED, 0);
    delay(500);
  }
}

void loop() {
 
  if (gsm.find("RING")) {                  // if have  RING
    gsm.println("AT+CLIP=1");              // turn on AT+CLIP=1  М590
    while (1) {
      if (gsm.find(T1)) {            // searching phone number
        if (digitalRead(key) == LOW) {
          off();
           
          gsm.println("AT+CLIP=0");            
          delay(500);
          gsm.println("ATH0");                 // "hanging dowd"
        }
        else if (digitalRead(key) == HIGH) {
          on();
          gsm.println("AT+CLIP=0");            
          delay(9000);
          gsm.println("ATH0");                 
        }
        break;                              
      }
      else {
        if (gsm.find(T2)) {            

          if (digitalRead(key) == LOW) {
            off();
            gsm.println("AT+CLIP=0");            
            delay(500);
            gsm.println("ATH0");                 
          }
          else if (digitalRead(key) == HIGH) {
            on();
            gsm.println("AT+CLIP=0");           
            delay(9000);
            gsm.println("ATH0");                 
          }
          break;                             
        }
        
        

        gsm.println("AT+CPAS");             // checking gsm module status
        //delay(100);
        if (gsm.find("+CPAS: 0")) break;    // if ready: +CPAS: 0
        //   if ringing: +CPAS: 3
        // looping
      }
    }
  }


    gsm.println("AT+COPS?");
    if (gsm.find("+COPS: 0")){
    analogWrite(LED, brigh);               
    }
    else{
      analogWrite(LED, brigh);
      delay(100);
    analogWrite(LED, 0);
    }
}

void on() {
  digitalWrite(r1, HIGH);
  int timer = 0;
  while (timer < 5) {
    if (digitalRead(key) == LOW) {
      break;
    }
    delay(100);
    timer++;
  }
  digitalWrite(r1, LOW);
}
void off() {
  digitalWrite(r2, LOW);
  int timer = 0;
  while (timer < 10) {
  
   if (digitalRead(key) == HIGH) {
      break;
    }
  delay(100);
  timer++;
}
  digitalWrite(r2, HIGH);
  if (digitalRead(key) == LOW) {
      delay(25000);
    } 
}

