int PUL = 7; //define Pulse pin
int DIR = 6; //define Direction pin
int ENA = 5; //define Enable Pin

void setup() {
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode (ENA, OUTPUT);

}
bool rotor_free(){
  digitalWrite(ENA, LOW);
  return false;
  }
bool rotor_hard(){
  digitalWrite(ENA, HIGH);
  return true;}
  
void rotor_run(float _rotations = 1, int _speed = 100, bool _direction = true) { //by default one full rotation with maximum speed
  int _steps = _rotations * 200; //converting rotations into steps
  int _d_time = map(constrain(_speed, 0, 100), 0, 100, 100000, 50); //converting speed from percents into delay time
  //      //map(value, fromLow, fromHigh, toLow, toHigh)
  for (int i = 0; i < _steps; i++)
  {
    digitalWrite(DIR, _direction);
    digitalWrite(ENA, HIGH);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(_d_time);
    digitalWrite(PUL, LOW);
    delayMicroseconds(_d_time);
  }
}
int sp=0;
void loop() {
  rotor_run(1, sp);
  rotor_free();
  sp+=5;
  delay(500);
}
