#ifndef LOCATION_USING_IP_ADDRESS_H
#define LOCATION_USING_IP_ADDRESS_H

#include <ArduinoJson.h>
#include <HTTPClient.h>

class Location
{
private:
    char *city;
    float latitude;
    float longitude;
    HTTPClient http;

public:
    Location();
    ~Location();
    void getLocation(const char *locationURL);
    char *getCity();
    float getLatitude();
    float getLongitude();
};

#endif