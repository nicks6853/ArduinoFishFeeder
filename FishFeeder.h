#ifndef FISH_FEEDER_H
#define FISH_FEEDER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Arduino_JSON.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <RTClib.h>
#include <RotaryEncoder.h>

#include "Definitions.h"
#include "Secrets.h"
#include "View.h"
#include "WelcomeView.h"

class FishFeeder {
   public:
    const char* fishFeederApiUrl =
        "https://ih1opc5t90.execute-api.ca-central-1.amazonaws.com/dev";

   private:
    Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT);
    RTC_DS3231 clock;
    View* view;
    RotaryEncoder* rotaryEncoder;
    int rotaryEncoderPos;
    int rotaryEncoderNewPos;
    int* feedingTimes;
    uint32_t lastFeedingTime;

    bool isDisplayOn;

   public:
    FishFeeder();
    void begin();
    void displayOff();
    void displayOn();
    bool getIsDisplayOn();
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
    uint32_t getLastFeedingTime();
    void setLastFeedingTime(uint32_t unixtime);
    int* getFeedingTimes();
    void refreshTime();
};

#endif