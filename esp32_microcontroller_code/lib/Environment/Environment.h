#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <ArduinoJson.h>
#include <Preferences.h>

class Environment
{
private:
    Preferences preferences;
    const char* ssidKey;
    char* ssidVal;
    const char* passKey;
    char* passVal;
    const char* weatherAPIKey;
    String weatherAPIValString;
    char* retrieveFromPreference(const char* key);

public:
    Environment();
    ~Environment();
    void begin();
    char* getSSID();
    char* getPassword();
    String getWeatherAPIValString();

    void setSSID(char* value);
    void setPassKey(char* value);
    void setWeatherAPIValString(char* value);

    // void freeVal(char * key);
};

#endif