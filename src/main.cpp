#include <Arduino.h>

#include <WiFi.h>

#include <Preferences.h>
#include <Location.h>


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

const char * ssidKey;
const char * ssidVal;

const char * passKey;
const char * passVal;


const char * city;
const char * latitude;
const char * longitude;
const char * locationURL = "https://ipapi.co/json/";



void setup() {
  Serial.begin(115200);
  // open or create new namespace for preference data in read/write mode (false for readonly)
  preferences.begin("wifi", false);
  // set wifi data, remove confidential info before committing and pushing.
  ssidKey = "ssid"; 
  ssidVal = ""; // manually add ssid if need to set

  passKey = "password";
  passVal = ""; // manually add password if need to set

  if (preferences.getString(ssidKey, "") == "")
    preferences.putString(ssidKey, ssidVal);
  if (preferences.getString(passKey, "") == "")
    preferences.putString(passKey, passVal);
  

  // connect to wifi
  WiFi.begin(preferences.getString(ssidKey, "").c_str(), preferences.getString(passKey, "").c_str());
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
  location myLocation = getLocation(locationURL, city, latitude, longitude); 
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println(preferences.getString(ssidKey));
  // Serial.println(preferences.getString(passKey));
}


