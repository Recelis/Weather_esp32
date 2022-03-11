#include "Location.h"
Location::Location()
{
}

void Location::getLocation(const char *locationURL)
{
    http.begin(locationURL);

    // Send HTTP GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        DynamicJsonDocument doc(5024);
        deserializeJson(doc, payload);

        city = strdup(doc["city"]); // doc["city"] get's overwritten by later uses of DynamicJSON therefore copy to city
        latitude = doc["latitude"];
        longitude = doc["longitude"];
        doc.clear();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
}

char *Location::getCity()
{
    return city;
}

float Location::getLatitude()
{
    return latitude;
}

float Location::getLongitude()
{
    return longitude;
}

Location::~Location()
{
}