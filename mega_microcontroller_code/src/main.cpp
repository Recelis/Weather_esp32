#include <Arduino.h>
// #include <SPI.h>          // f.k. for Arduino-1.5.2
// #include "Adafruit_GFX.h"// Hardware-specific library
// #include <MCUFRIEND_kbv.h>
// #include <string.h>

#include <Communication.h>
#include <LCD.h>

Communication myCommunication;
LCD myLCD;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  myLCD.startScreen();
  myLCD.refreshScreen();
}

void loop() {
  // put your main code here, to run repeatedly:
  bool newData = myCommunication.receiveData();
  // print screen only if new data is received
  if (newData){
    myLCD.refreshScreen(); // refresh screen
    myLCD.drawScreen(myCommunication.getReceivedChars());
    myCommunication.setNewData(false);
  }
}