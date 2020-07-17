//add saving settings to EEPROM, only if user turning on by the button
//add SLEEP MODE
//add alarm 
//add increasing and decreasing lightning when turning on/off

int bmax=220;//max brightness
int bled1 = bmax/2;//starting brightness
int hled1 = 1;//step of changing brightness
int bled2 = bmax/2;
int hled2 = 1;
int hh = 1;
int bb = bmax/2;//main brighness
int bl1;
int bl2;
int power1;
int power2;
//bool wawe = true;
void setup()  {
TCCR0B = TCCR0B & B11111000 | B00000001; 
  pinMode(1, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
    
      for (int i = 1; i <= bb; i++)
      {
      bl1=constrain(bled1, 1,bmax/2);
      bl2=constrain(bled2, 1,bmax/2);
      power1=map(bl1, 1, bmax/2, 0, i);
      power2=map(bl2, 1, bmax/2, 0, i); 
  
      analogWrite(6, power1);  
      analogWrite(5, power2);   
      delay(2000);
      }
  }
void loop()  {
  bool b0=digitalRead(2);
  bool b1=digitalRead(3);

  if (b0==false&&b1==false){
     bled1 = bmax/2;
     hled1 = 1;
     bled2 = bmax/2;
     bb = bmax/2;
     hled2 = 1;
     hh = 1;
     }
  if (b0==false&&b1==true){
     bled1=bled1-hled1;
     bled2=bled2+hled2;
  }
  if (b1==false&&b0==true){
     bb=bb+hh;}
     
  if (bb<=0||bb>=bmax){
    bb=constrain(bb,0,bmax);
    hh=-hh;}
    
  if (bled1<=1||bled1>=bmax){
    bled1=constrain(bled1,1,bmax);
    hled1=-hled1;}
    
  if (bled2<=1||bled2>=bmax){
    bled2=constrain(bled2,1,bmax);
    hled2=-hled2;}
     
      bl1=constrain(bled1, 1,bmax/2);
      bl2=constrain(bled2, 1,bmax/2);
      power1=map(bl1, 1, bmax/2, 0, bb);
      power2=map(bl2, 1, bmax/2, 0, bb); 
  
  analogWrite(6, power1);  
  analogWrite(5, power2);   
  delay(500);//speed of changing brighness and temperature
}
