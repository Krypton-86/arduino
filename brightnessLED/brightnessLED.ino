//дописати запис попередніх налаштувань в EEPROM, якщо!:користувач вимикає лампу кнопкою.
//додати SLEEP MODE
int bled1 = 125;
int hled1 = 1;
int bled2 = 125;
int hled2 = 1;
int bb=180;
int hh=1;
void setup()  {
  // устанваливаем пин 9 в режим выхода
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  //pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop()  {
  bool b0=digitalRead(0);
  bool b1=digitalRead(1);

  if (b0==false){
     bled1=bled1-hled1;
     bled2=bled2+hled2;
  }
  if (b1==false){
     bb=bb+hh;
            }
  if (bb==0||bb==250){
    hh=-hh;}
  if (bled1==1||bled1==250){
    hled1=-hled1;
  }
  if (bled2==1||bled2==250){
    hled2=-hled2;
  } 
  bled1=constrain(bled1, 1,250);
  bled2=constrain(bled2, 1,250);
  int power1=map(bled1, 1, 250, 0, bb);
  int power2=map(bled2, 1, 250, 0, bb); 
  
  analogWrite(6, power1);  
  analogWrite(5, power2);   
 

  // делаем паузу для достижения плавного наращивания/убывания яркости  
 
  delay(10);                           
} 
 

