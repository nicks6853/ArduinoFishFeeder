#ifndef SET_TIME_VIEW_H
#define SET_TIME_VIEW_H

#include "Definitions.h"
#include "HomeView.h"
#include "View.h"

class SetTimeView : public View {
   private:
    int step;
    uint32_t* feedingTimes;

   public:
    SetTimeView(FishFeeder* fishFeeder);
    void run();
    void handleInputs();
    void draw();
    void drawDefault(Adafruit_SSD1306* display, RTC_DS3231* clock);
    void drawStep1(Adafruit_SSD1306* display, RTC_DS3231* clock);
    void drawStep2(Adafruit_SSD1306* display, RTC_DS3231* clock);
    void handleInputsDefault();
    void handleInputsStep1();
    void handleInputsStep2();
    void runStep1();
    void runStep2();
};
#endif