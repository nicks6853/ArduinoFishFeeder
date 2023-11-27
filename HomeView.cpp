#include "HomeView.h"

#include "FishFeeder.h"

HomeView::HomeView(FishFeeder* fishFeederPtr) : View(fishFeederPtr) {}

void HomeView::run() {
    handleInputs();
    draw();
}

void HomeView::handleInputs() {
    int buttonPressed = digitalRead(BUTTON_PIN) == LOW;
    if (buttonPressed) {
        Serial.println("Button Pressed");
    }
}

void HomeView::draw() {
    Adafruit_SSD1306* display = fishFeeder->getDisplay();
    RTC_DS3231* clock = fishFeeder->getClock();
    DateTime now = clock->now();

    display->clearDisplay();
    display->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    display->setTextSize(1);
    display->setCursor(0, 0);
    display->print("Current Time");
    display->setCursor(128 - (4 * 8), 0);
    display->printf("%02d:%02d", now.hour(), now.minute());
    display->display();
}
