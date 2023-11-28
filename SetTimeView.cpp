#include "SetTimeView.h"

#include "FishFeeder.h"

SetTimeView::SetTimeView(FishFeeder* fishFeederPtr) : View(fishFeederPtr) {
    step = 0;

    feedingTimes = new uint32_t[4];
    feedingTimes[0] = 0;
    feedingTimes[1] = 0;
    feedingTimes[2] = 0;
    feedingTimes[3] = 0;

    feedingTimesIndex = 0;

    delay(500);
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
    display->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    display->print("Press button to set time");
    display->display();
}

void SetTimeView::drawStep1(Adafruit_SSD1306* display, RTC_DS3231* clock) {
    display->clearDisplay();
    display->setCursor(0, 0);
    display->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    display->print("Set Time 1:");
    display->setCursor(0, 8);

    display->setTextColor(
        feedingTimesIndex == 0 ? SSD1306_BLACK : SSD1306_WHITE,
        feedingTimesIndex == 0 ? SSD1306_WHITE : SSD1306_BLACK);
    display->printf("%02d", feedingTimes[0]);

    display->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    display->print(":");

    display->setTextColor(
        feedingTimesIndex == 1 ? SSD1306_BLACK : SSD1306_WHITE,
        feedingTimesIndex == 1 ? SSD1306_WHITE : SSD1306_BLACK);
    display->printf("%02d", feedingTimes[1]);

    display->display();
}

void SetTimeView::drawStep2(Adafruit_SSD1306* display, RTC_DS3231* clock) {}

void SetTimeView::handleInputsDefault() {
    int buttonPressed = digitalRead(BUTTON_PIN) == LOW;
    if (buttonPressed) {
        Serial.println("Button Pressed");

        // Reset the time
        feedingTimes[0], feedingTimes[1] = 0;
        step = 1;
    }
}
void SetTimeView::handleInputsStep1() {
    // Check if the rotary encoder switch was pressed
    int swPressed = digitalRead(ROTARY_SW_PIN) == LOW;

    if (swPressed) {
        if (feedingTimesIndex >= 1) {
            // TODO: Set the time
            Serial.println("Finished adding time");
        } else {
            feedingTimesIndex += 1;
        }
        delay(500);
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
        Serial.printf("dir: %d\n", direction);
        fishFeeder->setRotaryEncoderPos(fishFeeder->getRotaryEncoderNewPos());

        int newTotal = feedingTimes[feedingTimesIndex] + direction;
        feedingTimes[feedingTimesIndex] = newTotal > 0 ? newTotal : 0;
    }
}
void SetTimeView::handleInputsStep2() {}

void SetTimeView::runStep1() {}
void SetTimeView::runStep2() {}
