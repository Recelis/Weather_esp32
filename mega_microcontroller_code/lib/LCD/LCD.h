#ifndef LCD_H
#define LCD_H

#include <LCDBox.h>
#include <LCDBoxCurrent.h>

#include <Adafruit_I2CDevice.h>
#include <SPI.h>
#include "Adafruit_GFX.h"
#include <ArduinoJson.h>
#include <MCUFRIEND_kbv.h>
#include <stdio.h>

// Assign human-readable names to some common 16-bit color values:
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

#define MAX_WINDOW_WIDTH 120
#define MAX_WINDOW_HEIGHT 160
#define PADDING 4
#define DEFAULT_SCREEN_CHARACTER_X_WIDTH 6
#define DEFAULT_SCREEN_CHARACTER_X_HEIGHT 6

class LCD
{
private:
    MCUFRIEND_kbv tft;
    void drawBox(LCDBox box, int x, int y, char day);
    void drawCurrentBox(LCDBoxCurrent box);
    void floatToCharArr(float value, char* buff);
    int printmsg(int x, int y, int textSize, int color, const char *msg);

public:
    LCD();
    ~LCD();
    void startScreen();
    void refreshScreen();
    void drawScreen(char *receivedChars);
};

#endif