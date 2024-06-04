#ifndef WEATHER_H
#define WEATHER_H

#include <ArduinoJson.h>
#include <HTTPClient.h>

class Weather
{
private:
    char sevenDayForecast[1600];
    HTTPClient http;
    const char * weatherURL;
    // the following variables are unsigned longs because the time, measured in
    // milliseconds, will quickly become a bigger number than can be stored in an int.
    unsigned long lastTime = 0;
    // Timer set to 10 minutes (600000)
    // unsigned long timerDelay = 600000;
    // Set timer to 5 seconds (5000)
    // unsigned long timerDelay = 60000; // one minute
    unsigned long timerDelay = 600000;
    bool onStart = true;
    bool isNewData = false;
    void callWeatherAPI();
    void formatSevenDayForecast(char* payload);
public:
    Weather();
    ~Weather();
    void setWeatherURL(String urlString);
    bool getWeather(); // returns a value letting main know to getSevenDayForecast
    char * getSevenDayForecast();
};

#endif