#ifndef HOME_VIEW_H
#define HOME_VIEW_H

#include <Servo.h>

#include "Definitions.h"
#include "SetTimeView.h"
#include "View.h"

class HomeView : public View {
   private:
    uint32_t lastInput;
    Servo servo;

   public:
    HomeView(FishFeeder* fishFeederPtr, bool shouldPause = false);
    void run();
    void handleInputs();
    void draw();
    void checkTime();
};
#endif