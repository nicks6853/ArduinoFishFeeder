#include "FishFeeder.h"

FishFeeder::FishFeeder() {
    isDisplayOn = true;
    view = NULL;
    pinMode(BUTTON_PIN, INPUT_PULLUP);
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

uint32_t FishFeeder::getFeedingTime(unsigned int index) {
    return feedingTimes[index];
}

void FishFeeder::setFeedingTime(uint32_t feedingTime, unsigned int index) {
    Serial.printf("Setting feeding time at index %d to value: %d", index,
                  feedingTime);
    feedingTimes[index] = feedingTime;
}
