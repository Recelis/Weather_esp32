#include "LCDBox.h"
#include <stdio.h>

LCDBox::LCDBox()
{
}

/*
    Note: this is called before Serial.begin()
    and a lot of functions such as strcpy, atoa, etc, are not available!
*/
LCDBox::LCDBox(char* currDay, int boxIndex, float min, float max, float hum, char *main, char *description)
{
    const char* daysOfWeek[7];
    daysOfWeek[0] = "Sunday";
    daysOfWeek[1] = "Monday";
    daysOfWeek[2] = "Tuesday";
    daysOfWeek[3] = "Wednesday";
    daysOfWeek[4] = "Thursday";
    daysOfWeek[5] = "Friday";
    daysOfWeek[6] = "Saturday";
    
    dayOfWeek = daysOfWeek[0];
    
    for (int ii = 0; ii < 7; ii++) {
        bool isSame = true;
        for (int jj = 0; jj < 2; jj ++) {
            if (currDay[jj] != daysOfWeek[ii][jj]) {
                isSame = false;
                break;
            }
        }
        if (isSame) {
            int daysOfWeekIndex = (ii + boxIndex) % 7;
            // For some reason, daysOfWeekIndex can be larger than 7 even with modulus.
            // some part of this code is buggy 
            if (daysOfWeekIndex < 7) {
                dayOfWeek = daysOfWeek[daysOfWeekIndex];
            }
            break;
        }
    }
    tempMin = min;
    tempMax = max;
    humidity = hum;
    weatherMain = main;
    weatherDescription = description;
}

LCDBox::~LCDBox()
{
}