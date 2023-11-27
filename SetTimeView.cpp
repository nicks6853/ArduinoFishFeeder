#include "SetTimeView.h"

#include "FishFeeder.h"

SetTimeView::SetTimeView(FishFeeder* fishFeederPtr) : View(fishFeederPtr) {
    step = 0;

    feedingTimes = new uint32_t[4];
    feedingTimes[0] = 0;
    feedingTimes[1] = 0;
    feedingTimes[2] = 0;
    feedingTimes[3] = 0;
}

void SetTimeView::run() {
    switch (step) {
        case 1:
            runStep1();
            break;
        case 2:
            runStep2();
            break;
        default:
            break;
    }

    draw();          // Draw the fish icon
    handleInputs();  // Nothing to do here
}

void SetTimeView::handleInputs() {
    switch (step) {
        case 1:
            handleInputsStep1();
            break;
        case 2:
            handleInputsStep2();
            break;
        default:
            handleInputsDefault();
            break;
    }
}

void SetTimeView::draw() {
    Adafruit_SSD1306* display = fishFeeder->getDisplay();
    RTC_DS3231* clock = fishFeeder->getClock();

    switch (step) {
        case 1:
            drawStep1(display, clock);
            break;
        case 2:
            drawStep2(display, clock);
            break;
        default:
            drawDefault(display, clock);
            break;
    }
}

void SetTimeView::drawDefault(Adafruit_SSD1306* display, RTC_DS3231* clock) {
    display->clearDisplay();
    display->setCursor(0, 0);
    display->print("Press button to set time");
    display->display();
}

void SetTimeView::drawStep1(Adafruit_SSD1306* display, RTC_DS3231* clock) {
    display->clearDisplay();
    display->setCursor(0, 0);
    display->print("Set Time 1:");
    display->setCursor(0, 8);
    display->printf("%02d:%02d", feedingTimes[0], feedingTimes[1]);
    display->display();
}

void SetTimeView::drawStep2(Adafruit_SSD1306* display, RTC_DS3231* clock) {}

void SetTimeView::handleInputsDefault() {
    int buttonPressed = digitalRead(BUTTON_PIN) == LOW;
    if (buttonPressed) {
        Serial.println("Button Pressed");
        step = 1;
    }
}
void SetTimeView::handleInputsStep1() {
    // TODO: Add rotary encoder with interrupts
}
void SetTimeView::handleInputsStep2() {}

void SetTimeView::runStep1() {}
void SetTimeView::runStep2() {}
