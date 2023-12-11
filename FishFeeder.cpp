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

bool FishFeeder::getIsDisplayOn() { return isDisplayOn; }

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

void FishFeeder::refreshTime() {
    const char* timeApiUrl =
        "http://worldtimeapi.org/api/timezone/America/Moncton";

    const char ssid[] = SSID;
    const char password[] = PASSWORD;

    // BEGIN Initialize WiFi
    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    // END Initialize WiFi

    // Set the time for the clock
    WiFiClient client;
    HTTPClient http;

    http.begin(client, timeApiUrl);

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        JSONVar json = JSON.parse(payload);

        int unixtime = (int)json["unixtime"];
        int rawOffset = (int)json["raw_offset"];

        Serial.print("Unix time: ");
        Serial.println(unixtime + rawOffset);
        DateTime dt = DateTime(unixtime + rawOffset);
        clock.adjust(dt);
    } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
    WiFi.disconnect();
}
