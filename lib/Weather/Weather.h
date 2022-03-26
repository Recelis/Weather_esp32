#ifndef WEATHER_H
#define WEATHER_H

#include <ArduinoJson.h>
#include <HTTPClient.h>

class Weather
{
private:
    String sevenDayForecast;
    HTTPClient http;
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
    void callWeatherAPI(const char *weatherURL); // weatherURL is not saved locally in class to preserve memory
    void formatSevenDayForecast(String payload);
public:
    Weather();
    ~Weather();
    bool getWeather(const char *weatherURL); // returns a value letting main know to getSevenDayForecast
    String getSevenDayForecast();
};

#endif