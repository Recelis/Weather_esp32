#ifndef LCDBoxCurrent_H
#define LCDBoxCurrent_H

class LCDBoxCurrent
{
private:
public:
    char *location;
    float temp;
    float humidity;
    char *weatherMain;
    char *weatherDescription;
    LCDBoxCurrent();
    LCDBoxCurrent(char *loc, float t, float h, char *main, char *description);
    ~LCDBoxCurrent();
};

#endif
