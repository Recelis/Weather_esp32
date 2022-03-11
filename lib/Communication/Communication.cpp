#include "Communication.h"

// Serial1 to Mega values
#define RXD 16
#define TXD 17


Communication::Communication()
{
    // Set up Mega Serial
  Serial1.begin(9600, SERIAL_8N1, RXD, TXD);
}

void Communication::sendData(String sevenDayForecast, String location)
{
    // combines the location city data with weather data
    // send to Mega 
    DynamicJsonDocument doc(1500);
    deserializeJson(doc, sevenDayForecast);
    doc["location"] = location;
    char output[1500];
    serializeJson(doc, output);
    Serial1.print(output);
    Serial.println(output);
}

Communication::~Communication()
{
}