#include "FishFeeder.h"

FishFeeder::FishFeeder() {
    rotaryEncoderPos = 0;
    rotaryEncoder = NULL;
    isDisplayOn = true;
    view = NULL;

    // Initialize feeding times array to all zeros
    feedingTimes = new int[4];
    feedingTimes[0] = 0;
    feedingTimes[1] = 0;
    feedingTimes[2] = 0;
    feedingTimes[3] = 0;

    lastFeedingTime = UINT32_MAX;
}

void FishFeeder::begin() {
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    clock.begin();

    // Initialize the display to show the welcome view
    WelcomeView* welcomeView = new WelcomeView(this);
    view = welcomeView;
}

void FishFeeder::displayOff() {
    display.ssd1306_command(SSD1306_DISPLAYOFF);
    isDisplayOn = false;
}

void FishFeeder::displayOn() {
    display.ssd1306_command(SSD1306_DISPLAYON);
    isDisplayOn = true;
}

void FishFeeder::clearView() {
    if (view != NULL) {
        delete view;
    }

    view = NULL;
}

void FishFeeder::setView(View* viewPtr) {
    if (view != NULL) {
        clearView();
    }

    view = viewPtr;
}

void FishFeeder::run() {
    if (view != NULL && view->getGotoView() == NULL) {
        view->run();
    }

    if (view->getGotoView() != NULL) {
        // pt callback = view->getCallback();
        // callback(this);
        setView(view->getGotoView());
    }
}

Adafruit_SSD1306* FishFeeder::getDisplay() { return &display; }
RTC_DS3231* FishFeeder::getClock() { return &clock; }

RotaryEncoder* FishFeeder::getRotaryEncoder() { return rotaryEncoder; }
void FishFeeder::setRotaryEncoder(RotaryEncoder* rotaryEncoderPtr) {
    rotaryEncoder = rotaryEncoderPtr;
}

void FishFeeder::setRotaryEncoderPos(int pos) { rotaryEncoderPos = pos; }
void FishFeeder::setRotaryEncoderNewPos(int pos) { rotaryEncoderNewPos = pos; }
int FishFeeder::getRotaryEncoderPos() { return rotaryEncoderPos; }
int FishFeeder::getRotaryEncoderNewPos() { return rotaryEncoderNewPos; }
int* FishFeeder::getFeedingTimes() { return feedingTimes; }
uint32_t FishFeeder::getLastFeedingTime() { return lastFeedingTime; }
void FishFeeder::setLastFeedingTime(uint32_t unixtime) {
    lastFeedingTime = unixtime;
};
