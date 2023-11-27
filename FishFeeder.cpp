#include "FishFeeder.h"

FishFeeder::FishFeeder() {
    isDisplayOn = true;
    view = NULL;
    feedingTimes = NULL;

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

void FishFeeder::setFeedingTime(uint32_t* feedingTimesPtr) {
    feedingTimes = feedingTimesPtr;
}
