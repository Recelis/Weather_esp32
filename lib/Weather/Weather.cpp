#include "Weather.h"

Weather::Weather()
{
}

bool Weather::getWeather(const char *weatherURL)
{
    // checks that 10 mins have passed before sending new request
    if ((millis() - lastTime) > timerDelay | onStart)
    {
        callWeatherAPI(weatherURL);
        // send Serial data to Mega
        
        if (isNewData) {
            lastTime = millis(); // reset only if successful
            return true; // sending new data only if have been set true by weather response
        }
    }
    return false; // sending old data
}

void Weather::callWeatherAPI(const char *weatherURL)
{
    http.begin(weatherURL);

    // Send HTTP GET request
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        // Serial.println(payload);

        formatSevenDayForecast(payload);
        onStart = false; // let timer know to measure by time difference now.
        isNewData = true;
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
}

void Weather::formatSevenDayForecast(String payload)
{
    // get an arduinojson of http payload
    const int size = sizeof(payload);
    DynamicJsonDocument doc(1024);
    // apply filters
    StaticJsonDocument<500> filter;

    filter["current"]["temp"] = true;
    filter["current"]["weather"][0]["main"] = true;
    filter["current"]["weather"][0]["description"] = true;
    filter["current"]["humidity"] = true;

    filter["daily"][0]["temp"]["min"] = true;
    filter["daily"][0]["temp"]["max"] = true;
    filter["daily"][0]["weather"][0]["main"] = true;
    filter["daily"][0]["weather"][0]["description"] = true;
    filter["daily"][0]["humidity"] = true;

    deserializeJson(doc, payload, DeserializationOption::Filter(filter));
    serializeJson(doc, sevenDayForecast); // convert back to string
    doc.clear();
}

String Weather::getSevenDayForecast()
{
    return sevenDayForecast;
}

Weather::~Weather()
{
}