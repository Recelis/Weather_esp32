#include <Arduino.h>
#include <Preferences.h>
#include "config.h"

const char* THING_NAME_KEY = "THING_NAME";
const char* WIFI_SSID_KEY = "WIFI_SSID";
const char* WIFI_PASSWORD_KEY = "WIFI_PASSWORD";
const char* AWS_IOT_ENDPOINT_KEY = "AWS_IOT_ENDPNT";
const char* AWS_CERT_CA_KEY = "AWS_CERT_CA";
const char* AWS_CERT_CRT_KEY = "AWS_CERT_CRT";
const char* AWS_CERT_PRIVATE_KEY = "AWS_CERT_PRIVT";

void setup() {
  Serial.begin(9600);
  Serial.println("Writing values into EEPROM");
  Preferences preferences;
  preferences.begin("ESP32Monitoring", false);
  preferences.putString(THING_NAME_KEY, THING_NAME);
  Serial.println(THING_NAME_KEY);
  Serial.println(THING_NAME);
  preferences.putString(WIFI_SSID_KEY, WIFI_SSID);
  preferences.putString(WIFI_PASSWORD_KEY, WIFI_PASSWORD);
  preferences.putString(AWS_IOT_ENDPOINT_KEY, AWS_IOT_ENDPOINT);
  preferences.putString(AWS_CERT_CA_KEY, AWS_CERT_CA);
  preferences.putString(AWS_CERT_CRT_KEY, AWS_CERT_CRT);
  preferences.putString(AWS_CERT_PRIVATE_KEY, AWS_CERT_PRIVATE);

  Serial.println("Finished writing values to EEPROM");
  Serial.println("Validating values in EEPROM...");
  bool isValidate = true;
  isValidate = (preferences.getString(THING_NAME_KEY, THING_NAME)).equals(THING_NAME);
  isValidate = (preferences.getString(WIFI_SSID_KEY, WIFI_SSID)).equals(WIFI_SSID);
  isValidate = (preferences.getString(WIFI_PASSWORD_KEY, WIFI_PASSWORD)).equals(WIFI_PASSWORD);
  isValidate = (preferences.getString(AWS_IOT_ENDPOINT_KEY, AWS_IOT_ENDPOINT)).equals(AWS_IOT_ENDPOINT);
  isValidate = (preferences.getString(AWS_CERT_CA_KEY, AWS_CERT_CA)).equals(AWS_CERT_CA);
  isValidate = (preferences.getString(AWS_CERT_CRT_KEY, AWS_CERT_CRT)).equals(AWS_CERT_CRT);
  isValidate = (preferences.getString(AWS_CERT_PRIVATE_KEY, AWS_CERT_PRIVATE)).equals(AWS_CERT_PRIVATE);
  if (isValidate == false) {
    Serial.println("EEPROM did not save values correctly.");
  }
  else {
    Serial.println("EEPROM values validated!");
  }
}

void loop() {
  // do nothing
}
