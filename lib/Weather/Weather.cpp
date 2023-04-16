#include "Weather.h"

Weather::Weather()
{
}

void Weather::setWeatherURL(String urlString) 
{
    char* url = new char[urlString.length() + 1]; // set size of string block
    strcpy(url, urlString.c_str());
    weatherURL = url;
}

bool Weather::getWeather()
{
    // checks that 10 mins have passed before sending new request
    if (onStart | ((millis() - lastTime) > timerDelay))
    {
        callWeatherAPI();
        // send Serial data to Mega
        
        if (isNewData) {
            lastTime = millis(); // reset only if successful
            return true; // sending new data only if have been set true by weather response
        }
    }
    return false; // sending old data
}

void Weather::callWeatherAPI()
{
    http.begin(weatherURL);

    // Send HTTP GET request
    int httpResponseCode = http.GET();
    if (httpResponseCode == 200)
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
    DynamicJsonDocument doc(1600);
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
    memset(sevenDayForecast, 0, strlen(sevenDayForecast)); // reset sevenDayForecast
    serializeJson(doc, sevenDayForecast); // convert back to string
    doc.clear();
}

char * Weather::getSevenDayForecast()
{
    return sevenDayForecast;
}

Weather::~Weather()
{
}