#ifndef Communication_H
#define Communication_H

#include <ArduinoJson.h>

class Communication
{
private:
public:
    Communication();
    ~Communication();
    void sendData(char * sevenDayForecast, char * city);
};

#endif