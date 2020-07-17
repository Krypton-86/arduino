#include "OneButton.h"
OneButton button(A1, true);
void setup() {
  pinMode(13, OUTPUT);
  button.attachClick(myClickFunction);
  button.attachDoubleClick(myDoubleClickFunction);
}

void loop() {
  unsigned long now = millis();
  button.tick();
}
void myClickFunction() {
}

void myDoubleClickFunction() {
}
