#include "Communication.h"

// Serial1 to Mega values
#define RXD 16
#define TXD 17


Communication::Communication()
{
    // Set up Mega Serial
  Serial1.begin(9600, SERIAL_8N1, RXD, TXD);
}

void Communication::sendData(String sevenDayForecast, String)
{
    // combines the location city data with weather data
    // send to Mega

   Serial1.print(sevenDayForecast);
}

Communication::~Communication()
{
}