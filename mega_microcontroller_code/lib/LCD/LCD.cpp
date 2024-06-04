#include "LCD.h"

LCD::LCD()
{
}

void LCD::startScreen()
{
    uint16_t ID = tft.readID(); // id of LCD Screen
    if (ID == 0xD3D3)
        ID = 0x9481; // write-only shield
    tft.begin(ID);
}

void LCD::refreshScreen()
{
    tft.setRotation(1);
    tft.fillScreen(BLACK);
}

void LCD::drawScreen(char *receivedChars)
{
    // convert receivedChars arduinojson
    DynamicJsonDocument doc(1000);
    deserializeJson(doc, receivedChars);
    
    char * dayOfWeek = doc["dayOfWeek"];
    Serial.println(dayOfWeek);
    // set the box objects
    LCDBoxCurrent boxCurrent(doc["location"], doc["current"]["temp"], doc["current"]["humidity"], doc["current"]["weather"][0]["main"], doc["current"]["weather"][0]["description"]);

    LCDBox box0(doc["dayOfWeek"], 0, doc["daily"][0]["temp"]["min"], doc["daily"][0]["temp"]["max"], doc["daily"][0]["humidity"], doc["daily"][0]["weather"][0]["main"], doc["daily"][0]["weather"][0]["description"]);

    LCDBox box1(doc["dayOfWeek"], 1, doc["daily"][1]["temp"]["min"], doc["daily"][1]["temp"]["max"], doc["daily"][1]["humidity"], doc["daily"][1]["weather"][0]["main"], doc["daily"][1]["weather"][0]["description"]);

    LCDBox box2(doc["dayOfWeek"], 2, doc["daily"][2]["temp"]["min"], doc["daily"][2]["temp"]["max"], doc["daily"][2]["humidity"], doc["daily"][2]["weather"][0]["main"], doc["daily"][2]["weather"][0]["description"]);

    LCDBox box3(doc["dayOfWeek"], 3, doc["daily"][3]["temp"]["min"], doc["daily"][3]["temp"]["max"], doc["daily"][3]["humidity"], doc["daily"][3]["weather"][0]["main"], doc["daily"][3]["weather"][0]["description"]);

    LCDBox box4(doc["dayOfWeek"], 4, doc["daily"][4]["temp"]["min"], doc["daily"][4]["temp"]["max"], doc["daily"][4]["humidity"], doc["daily"][4]["weather"][0]["main"], doc["daily"][4]["weather"][0]["description"]);

    LCDBox box5(doc["dayOfWeek"], 5, doc["daily"][5]["temp"]["min"], doc["daily"][5]["temp"]["max"], doc["daily"][5]["humidity"], doc["daily"][5]["weather"][0]["main"], doc["daily"][5]["weather"][0]["description"]);

    LCDBox box6(doc["dayOfWeek"], 6, doc["daily"][6]["temp"]["min"], doc["daily"][6]["temp"]["max"], doc["daily"][6]["humidity"], doc["daily"][6]["weather"][0]["main"], doc["daily"][6]["weather"][0]["description"]);

    // drawing has to take place from left to right so that
    // any overwriting cuts things off
    drawCurrentBox(boxCurrent);
    drawBox(box0, 120, 6, '0');
    drawBox(box1, 240, 6, '1');
    drawBox(box2, 360, 6, '2');

    drawBox(box3, 6, 160, '3');
    drawBox(box4, 120, 160, '4');
    drawBox(box5, 240, 160, '5');
    drawBox(box6, 360, 160, '6');


}

void LCD::drawCurrentBox(LCDBoxCurrent box)
{
    int currentX = 6;
    int currentY = 6;
    currentY = printmsg(currentX, currentY, 1, WHITE, "Current");
    currentY = printmsg(currentX, currentY, 2, YELLOW, box.weatherMain);
    currentY = printmsg(currentX, currentY, 1, WHITE, box.weatherDescription);
    char tempBuff[10]; // create memory buffs outside for inside scope access
    floatToCharArr(box.temp, tempBuff);
    strcat(tempBuff, "C");
    currentY = printmsg(currentX, currentY, 2, BLUE, tempBuff);

    char humBuff[10]; // create memory buffs outside for inside scope access
    floatToCharArr(box.humidity, humBuff);
    strcat(humBuff, "%");
    currentY = printmsg(currentX, currentY, 2, GREEN, humBuff);
    currentY = printmsg(currentX, currentY, 2, RED, box.location);
}

void LCD::drawBox(LCDBox box, int x, int y, char day)
{
    int currentY = y;
    char dayVal[10];
    if (day == '0')
    {
        strcpy(dayVal, "Today");
    }
    else if (day == '1')
    {
        strcpy(dayVal, "Tomorrow");
    }
    else
    {
        strcpy(dayVal, box.dayOfWeek);
        char dayStr[2] = {'\0'};
        strcat(dayVal, dayStr);
    }
    currentY = printmsg(x, currentY, 1, WHITE, dayVal);
    currentY = printmsg(x, currentY, 2, YELLOW, box.weatherMain);
    currentY = printmsg(x, currentY, 1, WHITE, box.weatherDescription);

    char tempMinBuff[10]; // create memory buffs outside for inside scope access
    floatToCharArr(box.tempMin, tempMinBuff);
    char tempMaxBuff[10];
    floatToCharArr(box.tempMax, tempMaxBuff);

    // concat tempMin and tempMax
    char tempBuff[60];
    strcpy(tempBuff, tempMinBuff);
    strcat(tempBuff, " - ");
    strcat(tempBuff, tempMaxBuff);
    strcat(tempBuff, "C");
    currentY = printmsg(x, currentY, 1, WHITE, tempBuff);

    char humBuff[10];
    floatToCharArr(box.humidity, humBuff);
    strcat(humBuff, "%");
    currentY = printmsg(x, currentY, 1, WHITE, humBuff);
}

void LCD::floatToCharArr(float value, char *buff)
{
    int val_int = (int)value;                     // compute the integer part of the float
    int val_fra = (int)((value - val_int) * 100); // compute 2 decimal places (and convert it to int)
    sprintf(buff, "%d.%02d", val_int, val_fra);   // create a string with the 'floated' value including preceding 0s
    return buff;
}

// returns the new y location (including padding of 2) factoring in the textSize
int LCD::printmsg(int x, int y, int textSize, int color, const char *msg)
{
    // split across multiple rows if too long
    // calculate width of added tokens
    // if longer than MAX_WINDOW_WIDTH
    // start new line
    const char *delimiter = " ";
    char *token;
    char testMsg[100]; // can use malloc but not working

    strncpy(testMsg, msg, sizeof(testMsg));
    token = strtok(testMsg, delimiter);
    int tokenWidth = strlen(token) * DEFAULT_SCREEN_CHARACTER_X_WIDTH * textSize;

    if (tokenWidth > MAX_WINDOW_WIDTH)
    {
        textSize = 1; // set textSize to smallest value
    }
    // for second + tokens
    while (token != NULL)
    {
        token = strtok(NULL, delimiter);
        tokenWidth = strlen(token) * DEFAULT_SCREEN_CHARACTER_X_WIDTH * textSize; // recalculate token width
        // see if any tokens are wider than MAX_WINDOW_WIDTH
        if (tokenWidth > MAX_WINDOW_WIDTH)
        {
            textSize = 1; // set textSize to smallest value
        }
    }

    tft.setTextColor(color, BLACK);
    tft.setTextSize(textSize); // default 6*8 (x,y)
    tft.setCursor(x, y);
    // Tokenise actual msg
    token = strtok(msg, delimiter);
    tokenWidth = (strlen(token) + 1) * DEFAULT_SCREEN_CHARACTER_X_WIDTH * textSize; // reuse tokenWidth
    tft.println(token);
    int xPos = x + tokenWidth;
    tft.setCursor(xPos, y); // move to right

    int lineWidth = tokenWidth; // calculate current point in line;

    // loop through rest of tokens
    while (token != NULL)
    {
        token = strtok(NULL, delimiter);
        tokenWidth = (strlen(token) + 1) * DEFAULT_SCREEN_CHARACTER_X_WIDTH * textSize; // reuse tokenWidth
        lineWidth = lineWidth + tokenWidth; // calculate current point in line
        
        if (lineWidth > MAX_WINDOW_WIDTH)
        {
            xPos = x;                 // set x position to be start
            y = 8 * textSize + PADDING + y; // set new line
            lineWidth = tokenWidth;
        }
        tft.setCursor(xPos, y); // include space at end
        tft.println(token);
        xPos = xPos + (strlen(token) + 1) * DEFAULT_SCREEN_CHARACTER_X_WIDTH * textSize; // reset new xPos
    }

    return DEFAULT_SCREEN_CHARACTER_X_HEIGHT * textSize + PADDING + y;
}

LCD::~LCD()
{
}