#include <Arduino.h>

#include <WiFi.h>
#include <Location.h>
#include <Weather.h>
#include <Communication.h>
#include <Environment.h>
#include <DayOfWeek.h>

/*
  ESP32 Weather built on PlatformIO.

    Functionality
      Config Mode
        sets EEPROM using Preferences.h for wifi ssid and password

      Start
        on start, will get location of Weather Viewer using IP address

      Every half hour
        calls open-weather endpoint
        extracts 7 days weather data using ArduinoJSON and builds an object containing resulting data
        serialises results and sends to Arduino Mega.

*/

const char *locationURL = "https://ipapi.co/json/";

// initialise Location object
Location myLocation;

// initialise weather object
Weather myWeather;

// initialise communication object
Communication myCommunication;

// initialise environment object
Environment myEnvironment;

// initialise day of week object
DayOfWeek myDayOfWeek;

void setup()
{
  Serial.begin(115200);
  // connect to wifi
  myEnvironment.begin();
  WiFi.begin(myEnvironment.getSSID(), myEnvironment.getPassword()); // NEEDS const char * as input args
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  // get location city, latitude and longitude of device

  myLocation.getLocation(locationURL);
  String weatherURLString = "https://api.openweathermap.org/data/2.5/onecall?lat=" 
    + String(myLocation.getLatitude()) 
    + "&lon=" + String(myLocation.getLongitude()) 
    + "&exclude=minutely,hourly&units=metric&appid=" 
    + myEnvironment.getWeatherAPIValString();
  Serial.println(weatherURLString);
  myWeather.setWeatherURL(weatherURLString);
  myDayOfWeek.requestDayOfWeek(myLocation.getLatitude(), myLocation.getLongitude());
}

void loop()
{
  bool isNewData = myWeather.getWeather();
  // if newWeatherData then send to Mega
  if (isNewData)
  {
    Serial.println("Sending new Data:");
    char * sevenDayForecast = myWeather.getSevenDayForecast();
    myCommunication.sendData(sevenDayForecast, myLocation.getCity(), myDayOfWeek.getDayOfWeek());
  }
}
