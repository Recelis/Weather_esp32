#ifndef LOCATION_USING_IP_ADDRESS_H
#define LOCATION_USING_IP_ADDRESS_H

struct location
{
    const char *city;
    const char *latitude;
    const char *longitude;
};


location getLocation(const char *locationURL, const char *city, const char *latitude, const char *longitude);

#endif