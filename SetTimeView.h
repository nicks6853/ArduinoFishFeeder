#ifndef SET_TIME_VIEW_H
#define SET_TIME_VIEW_H

#include "Definitions.h"
#include "HomeView.h"
#include "View.h"

class SetTimeView : public View {
   private:
    int step;
    int workingIndex;

   public:
    SetTimeView(FishFeeder* fishFeeder, bool shouldPause = false);

    void run();
    void runDefault();

    void draw();
    void drawDefault(Adafruit_SSD1306* display, RTC_DS3231* clock);

    void handleInputs();
    void handleInputsDefault();
};
#endif