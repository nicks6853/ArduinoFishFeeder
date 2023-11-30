# Fish Feeder

Fun project to create an automated fish feeder with an ESP8266, rotary encoder, OLED display and a servo motor.

## Setup

To get this working, you need to add a file called `Secrets.h` to the root of this folder. It should contain your Wifi SSID and password like this.

```cpp
#define SSID YOUR_SSID
#define PASSWORD YOUR_PASSWORD
```

You will also need the following libraries:
- [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [RotaryEncoder](https://github.com/mathertel/RotaryEncoder)
- [RTClib](https://github.com/adafruit/RTClib)

Connect a SSD1306 128x32 OLED display to the I2C pins as well as a rotary encoder and servo to the correct pins from Definitions.h on your NodeMCU ESP8266. Then, simply flash the program using the Arduino editor.