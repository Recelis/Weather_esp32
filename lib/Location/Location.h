#ifndef LOCATION_USING_IP_ADDRESS_H
#define LOCATION_USING_IP_ADDRESS_H

#include <ArduinoJson.h>
#include <HTTPClient.h>

class Location
{
    private: 
        const char *city;
        float latitude;
        float longitude;
        HTTPClient http;
        
    public:
        Location();
        ~Location();
        void getLocation(const char * locationURL);
        const char * getCity();
        float getLatitude();
        float getLongitude();
};

#endif