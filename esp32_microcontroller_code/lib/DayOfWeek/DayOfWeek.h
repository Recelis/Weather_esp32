#ifndef DAYOFWEEK_H
#define DAYOFWEEK_H

#include <ArduinoJson.h>
#include <HTTPClient.h>

class DayOfWeek
{
private:
    HTTPClient http;
    char* dayOfWeek;

public:
    DayOfWeek();
    ~DayOfWeek();
    void requestDayOfWeek(float latitude, float longitude);
    char* getDayOfWeek();
};

#endif