#include <Arduino.h>

#include <WiFi.h>

#include <Preferences.h>
#include <Location.h>
#include <Weather.h>
#include <Communication.h>

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

Preferences preferences;

const char *ssidKey;
char *ssidVal;

const char *passKey;
char *passVal;

const char *locationURL = "https://ipapi.co/json/";

const char *weatherAPIKey;
char *weatherURL;

// initialise Location object
Location myLocation;

// initialise weather object
Weather myWeather;

// initialise communication object
Communication myCommunication;

void setup()
{
  Serial.begin(115200);
  // open or create new namespace for preference data in read/write mode (false for readonly)
  preferences.begin("wifi", false);
  // set wifi data, remove confidential info before committing and pushing.
  // c_str() always refers to internal location which can be overwritten
  // so need to copy the string into a char* address
  ssidKey = "ssid";
  String ssidValString = preferences.getString(ssidKey, "");
  ssidVal = new char[ssidValString.length() + 1]; // set size of string block
  strcpy(ssidVal, preferences.getString(ssidKey, "").c_str());
  Serial.println(ssidVal);

  passKey = "password";
  String passValString = preferences.getString(passKey, "");
  passVal = new char[passValString.length() + 1]; // set size of string block
  strcpy(passVal, passValString.c_str());
  Serial.println(passVal);

  weatherAPIKey = "weatherAPI";
  String weatherAPIValString = preferences.getString(weatherAPIKey, "");

  // if (ssidVal == "")
  //   preferences.putString(ssidKey, ""); // manually add ssid if need to set
  // if (passVal == "")
  //   preferences.putString(passKey, ""); // manually add password if need to set
  // if (weatherAPIValString == "")
  //   preferences.putString(weatherAPIKey, ""); // manually add weatherapival if need to set

  Serial.println(weatherAPIValString);
  // connect to wifi
  WiFi.begin(ssidVal, passVal); // NEEDS const char * as input args
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
  String weatherURLString = "https://api.openweathermap.org/data/2.5/onecall?lat=" + String(myLocation.getLatitude()) + "&lon=" + String(myLocation.getLongitude()) + "&exclude=minutely,hourly&units=metric&appid=" + weatherAPIValString;
  weatherURL = new char[weatherURLString.length() + 1]; // set size of string block
  strcpy(weatherURL, weatherURLString.c_str());         // save to global const char *
}

void loop()
{
  bool isNewData = myWeather.getWeather(weatherURL);
  // if newWeatherData then send to Mega
  if (isNewData)
  {
    Serial.println("Sending new Data:");
    char * sevenDayForecast = myWeather.getSevenDayForecast();
    myCommunication.sendData(sevenDayForecast, myLocation.getCity());
  }
}
