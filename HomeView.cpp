#include "HomeView.h"

#include "FishFeeder.h"

HomeView::HomeView(FishFeeder* fishFeederPtr, bool shouldPause)
    : View(fishFeederPtr, shouldPause) {}

void HomeView::run() {
    draw();

    if (shouldPause) {
        delay(250);
        shouldPause = false;
    }

    handleInputs();
    checkTime();
}

void HomeView::handleInputs() {
    int buttonPressed = digitalRead(ROTARY_SW_PIN) == LOW;
    if (buttonPressed) {
        // Go to set time view
        SetTimeView* setTimeView = new SetTimeView(fishFeeder, true);
        gotoView = setTimeView;
    }
}

void HomeView::draw() {
    Adafruit_SSD1306* display = fishFeeder->getDisplay();
    RTC_DS3231* clock = fishFeeder->getClock();
    DateTime now = clock->now();
    uint32_t currentUnixTime = now.unixtime();
    int* feedingTimes = fishFeeder->getFeedingTimes();
    int lastFeedingTime = fishFeeder->getLastFeedingTime();
    int timeSinceLastFeed = currentUnixTime - lastFeedingTime;

    display->clearDisplay();
    display->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    display->setTextSize(1);
    display->setCursor(0, 0);
    display->print("Current Time");
    display->setCursor(128 - (4 * 8), 0);
    display->printf("%02d:%02d", now.hour(), now.minute());

    display->setCursor(0, 16);
    display->printf("%02d:%02d", feedingTimes[0], feedingTimes[1]);

    display->setCursor(0, 24);
    display->printf("%02d:%02d", feedingTimes[2], feedingTimes[3]);

    if (timeSinceLastFeed > 0 && timeSinceLastFeed < 5) {
        display->setCursor(48, 24);
        display->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
        display->print("Feeding...");
    }

    display->display();
}

void HomeView::checkTime() {
    RTC_DS3231* clock = fishFeeder->getClock();
    DateTime now = clock->now();
    uint32_t currentUnixTime = now.unixtime();
    int lastFeedingTime = fishFeeder->getLastFeedingTime();
    int timeSinceLastFeed = currentUnixTime - lastFeedingTime;

    int hour = now.hour();
    int minute = now.minute();

    int* feedingTimes = fishFeeder->getFeedingTimes();

    Serial.println(DateTime(lastFeedingTime).timestamp());

    if (lastFeedingTime == UINT32_MAX || timeSinceLastFeed > 60) {
        Serial.println("Checking time");
        if ((hour == feedingTimes[0] && minute == feedingTimes[1]) ||
            (hour == feedingTimes[2] && minute == feedingTimes[3])) {
            fishFeeder->setLastFeedingTime(currentUnixTime / 60 * 60);
        }
    }
}
