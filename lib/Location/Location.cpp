


#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Location.h"

location getLocation(const char *locationURL, const char *city, const char *latitude, const char *longitude)
{
    HTTPClient http;
    http.begin(locationURL);

    // Send HTTP GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        DynamicJsonDocument doc(5024);
        deserializeJson(doc, payload);
        city = doc["city"];
        latitude = doc["latitude"];
        longitude = doc["longitude"];

    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
    location locationData;
    locationData.city = city;
    locationData.latitude = latitude;
    locationData.longitude = longitude;
    return locationData;
}

