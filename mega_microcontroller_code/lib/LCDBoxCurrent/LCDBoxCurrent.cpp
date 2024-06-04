#include "LCDBoxCurrent.h"

LCDBoxCurrent::LCDBoxCurrent()
{
    
}

LCDBoxCurrent::LCDBoxCurrent(char * loc, float t, float h, char * main, char * description)
{
    location = loc;
    temp = t;
    humidity = h;
    weatherMain = main;
    weatherDescription = description;
}

LCDBoxCurrent::~LCDBoxCurrent()
{
}