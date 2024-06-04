# Weather_mega

Part of the Weather Viewer system.

Receives a JSON string containing Weather forecast data for the next 7 days as well as current weather details.

Displays onto a 3.5" tft screen.

Entry file is /src/main.cpp

All library files are found in /lib

Communication lib for receiving data from esp32

LCD lib for printing text and refreshing screen.

LCDBox is a standardised LCD section for printing one of the seven day forecasts.

LCDCurrentBox is a LCD section for printing the current weather.

To Set Up:
- Install VS Code
- Install PlatformIO https://platformio.org/
Additional Libraries
- ArduinoJSON
- Adafruit GFX Library
- MCUFRIEND_kbv

All libraries are included in platformio.ini file.
