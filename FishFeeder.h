#ifndef FISH_FEEDER_H
#define FISH_FEEDER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <RTClib.h>

#include "Definitions.h"
#include "View.h"
#include "WelcomeView.h"

class FishFeeder {
   private:
    Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT);
    RTC_DS3231 clock;
    View* view;

    uint32_t feedingTimes[2];

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
    uint32_t getFeedingTime(unsigned int index);
    void setFeedingTime(uint32_t feedingTime, unsigned int index);
};

#endif