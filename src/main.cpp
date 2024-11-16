#include "gui/gui.hpp"

GUI* myGUI;

void setup(){
  Serial.begin(9600);
  myGUI = new GUI(10); // frame rate : 30 fps
}

void loop() {
  myGUI->run();
}