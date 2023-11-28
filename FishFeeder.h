#ifndef FISH_FEEDER_H
#define FISH_FEEDER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <RTClib.h>
#include <RotaryEncoder.h>

#include "Definitions.h"
#include "View.h"
#include "WelcomeView.h"

class FishFeeder {
   private:
    Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT);
    RTC_DS3231 clock;
    View* view;
    RotaryEncoder* rotaryEncoder;
    int rotaryEncoderPos;
    int rotaryEncoderNewPos;

    // uint32_t* feedingTimes;

    bool isDisplayOn;

   public:
    FishFeeder();
    void begin();
    void displayOff();
    void displayOn();
    Adafruit_SSD1306* getDisplay();
    RTC_DS3231* getClock();
    void run();
    void clearView();
    void setView(View* viewPtr);
    // void setFeedingTime(uint32_t* feedingTimesPtr);
    RotaryEncoder* getRotaryEncoder();
    void setRotaryEncoder(RotaryEncoder* rotaryEncoderPtr);
    void setRotaryEncoderPos(int pos);
    void setRotaryEncoderNewPos(int pos);
    int getRotaryEncoderPos();
    int getRotaryEncoderNewPos();
};

#endif