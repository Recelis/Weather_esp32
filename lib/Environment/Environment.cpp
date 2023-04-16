#include "Environment.h"
/*
    Wrapper class for Preferences
    to call environment values.
*/
Environment::Environment()
{
    ssidKey = "ssid";
    passKey = "password";
    weatherAPIKey = "weatherAPI";
}

void Environment::begin() {
    // open or create new namespace for preference data in read/write mode (false for readonly)
    preferences.begin("wifi", false);
}

char* Environment::retrieveFromPreference(const char* key)
{

    String valString = preferences.getString(key, "");
    char* value = new char[valString.length() + 1]; // set size of string block
    
    strcpy(value, preferences.getString(key, "").c_str());
    Serial.println(value);
    return value;
}

char* Environment::getSSID() 
{
    ssidVal = retrieveFromPreference(ssidKey);
    return ssidVal;
}

char* Environment::getPassword() 
{
    passVal = retrieveFromPreference(passKey);
    return passVal;
}

String Environment::getWeatherAPIValString()
{
    String weatherAPIValString = preferences.getString(weatherAPIKey, "");
    return weatherAPIValString;
}

void Environment::setSSID(char* value) {
    preferences.putString(ssidKey, value);
}

void Environment::setPassKey(char* value) {
    preferences.putString(passKey, value);
}

void Environment::setWeatherAPIValString(char* value) {
    preferences.putString(weatherAPIKey, value);
}

// void Environment::freeVal(char * key)
// {
//     switch (key) {
//         case ssidKey: {
//             free(ssidVal);
//         }
//         case passKey: {
//             free(passVal);
//         }
//         default:
//             return
//     }
//     free(passVal);
// }

Environment::~Environment()
{
}

