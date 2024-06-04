#ifndef Communication_H
#define Communication_H

#include <string.h>

class Communication
{
private:
    const int numChars = 6000;
    char receivedChars[6000];
    bool newData = false;

public:
    Communication();
    ~Communication();
    bool receiveData();
    char * getReceivedChars();
    void setNewData(bool newDataFlag);
};

#endif