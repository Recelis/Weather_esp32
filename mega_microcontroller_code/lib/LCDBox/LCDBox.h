#ifndef LCDBox_H
#define LCDBox_H

#include "LCDBoxCurrent.h"

class LCDBox : public LCDBoxCurrent
{
    // draws a box with weather details
    private:
        
    public:
        float tempMin;
        float tempMax;
        const char* dayOfWeek;
        LCDBox();
        LCDBox(char* currDay, int boxIndex, float min, float max, float hum, char * main, char * description);
        ~LCDBox();
};

#endif