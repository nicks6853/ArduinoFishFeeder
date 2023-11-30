#include "SetTimeView.h"

#include "FishFeeder.h"

SetTimeView::SetTimeView(FishFeeder* fishFeederPtr, bool shouldPause)
    : View(fishFeederPtr, shouldPause) {
    step = 0;
    workingIndex = 0;
}

void SetTimeView::run() {
    switch (step) {
        case 0:
            runDefault();
            break;
        default:
            break;
    }

    draw();  // Draw to the display

    if (shouldPause) {
        delay(250);
        shouldPause = false;
    }

    handleInputs();  // Handle inputs depending on the screen
}

void SetTimeView::handleInputs() {
    switch (step) {
        case 0:
            handleInputsDefault();
            break;
        default:
            break;
    }
}

void SetTimeView::draw() {
    Adafruit_SSD1306* display = fishFeeder->getDisplay();
    RTC_DS3231* clock = fishFeeder->getClock();

    switch (step) {
        case 0:
            drawDefault(display, clock);
            break;
        default:
            break;
    }
}

void SetTimeView::drawDefault(Adafruit_SSD1306* display, RTC_DS3231* clock) {
    int* feedingTimes = fishFeeder->getFeedingTimes();

    display->clearDisplay();
    display->setCursor(0, 0);
    display->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    display->print("Set Time:");
    display->setCursor(0, 16);

    // Print first time
    display->print("1: ");
    display->setTextColor(workingIndex == 0 ? SSD1306_BLACK : SSD1306_WHITE,
                          workingIndex == 0 ? SSD1306_WHITE : SSD1306_BLACK);
    display->printf("%02d", feedingTimes[0]);

    display->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    display->print(":");

    display->setTextColor(workingIndex == 1 ? SSD1306_BLACK : SSD1306_WHITE,
                          workingIndex == 1 ? SSD1306_WHITE : SSD1306_BLACK);
    display->printf("%02d", feedingTimes[1]);

    // Print second time
    display->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    display->setCursor(0, 24);
    display->print("2: ");

    display->setTextColor(workingIndex == 2 ? SSD1306_BLACK : SSD1306_WHITE,
                          workingIndex == 2 ? SSD1306_WHITE : SSD1306_BLACK);
    display->printf("%02d", feedingTimes[2]);

    display->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    display->print(":");

    display->setTextColor(workingIndex == 3 ? SSD1306_BLACK : SSD1306_WHITE,
                          workingIndex == 3 ? SSD1306_WHITE : SSD1306_BLACK);
    display->printf("%02d", feedingTimes[3]);

    display->display();
}

void SetTimeView::handleInputsDefault() {
    int* feedingTimes = fishFeeder->getFeedingTimes();

    // Check if the rotary encoder switch was pressed
    int swPressed = digitalRead(ROTARY_SW_PIN) == LOW;

    if (swPressed) {
        if (workingIndex >= 3) {
            Serial.println("Finished adding time");
            // Save pointer to current view to clear memory
            View* previousView = gotoView;

            // Go back to home view
            HomeView* homeView = new HomeView(fishFeeder, true);
            gotoView = homeView;

            // Clear memory of previous view
            delete previousView;
        } else {
            workingIndex += 1;
        }
        shouldPause = true;
    }

    // Check the rotary encoder
    RotaryEncoder* rotaryEncoder = fishFeeder->getRotaryEncoder();
    rotaryEncoder->tick();
    int rotaryEncoderPos = fishFeeder->getRotaryEncoderPos();
    int rotaryEncoderNewPos = fishFeeder->getRotaryEncoderNewPos();

    fishFeeder->setRotaryEncoderNewPos(rotaryEncoder->getPosition());

    if (fishFeeder->getRotaryEncoderPos() !=
        fishFeeder->getRotaryEncoderNewPos()) {
        // Can only getDirection() once per cycle
        int direction = (int)(rotaryEncoder->getDirection());
        fishFeeder->setRotaryEncoderPos(fishFeeder->getRotaryEncoderNewPos());

        int clampUpperLimit = workingIndex % 2 == 0 ? 23 : 59;

        int newTotal = std::clamp(feedingTimes[workingIndex] + direction, 0,
                                  clampUpperLimit);
        feedingTimes[workingIndex] = newTotal;
    }
}

void SetTimeView::runDefault() {}
