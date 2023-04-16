#include "DayOfWeek.h"
/*
    Calls TimeAPI to get dayOfWeek.
*/
DayOfWeek::DayOfWeek() {}

void DayOfWeek::requestDayOfWeek(String ipAddress) {
    String timeApiURLString = "https://www.timeapi.io/api/Time/current/ip?ipAddress=" + ipAddress;
    const char* timeApiURL = timeApiURLString.c_str();
    http.begin(timeApiURL);

    // Send HTTP GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode == HTTP_CODE_OK)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        DynamicJsonDocument doc(5024);
        deserializeJson(doc, payload);

        dayOfWeek = strdup(doc["dayOfWeek"]); // doc["city"] get's overwritten by later uses of DynamicJSON therefore copy to city
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

char* DayOfWeek::getDayOfWeek() {
    return dayOfWeek;
}

DayOfWeek::~DayOfWeek()
{
}

