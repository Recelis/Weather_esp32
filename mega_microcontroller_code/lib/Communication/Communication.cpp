#include <Arduino.h>
#include "Communication.h"

Communication::Communication()
{
  // Set up Mega Serial
  Serial1.begin(9600);
}

/*
  Receives data from Serial1, only stopping when a \0 character is found.
*/
bool Communication::receiveData()
{
  static short int ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial1.available() > 0 && newData == false)
  {
    if (ndx == 0){
      // reset receivedChars to be all empty strings
      memset(receivedChars, 0, strlen(receivedChars));
    }

    rc = Serial1.read();
    if (rc != endMarker && ndx < numChars)
    {
      receivedChars[ndx] = rc;
      ndx++;
    }
    else
    {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
  return newData; // lets the main program know that data has been received.
}

/*
  Simple Getter
*/
char * Communication::getReceivedChars(){
  return receivedChars;
}

/*
  Sets flag for sending printing new data to screen.
*/
void Communication::setNewData(bool newDataFlag){
  newData = newDataFlag;
}

Communication::~Communication()
{
}
