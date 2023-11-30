#ifndef HOME_VIEW_H
#define HOME_VIEW_H

#include "Definitions.h"
#include "SetTimeView.h"
#include "View.h"

class HomeView : public View {
   public:
    HomeView(FishFeeder* fishFeederPtr, bool shouldPause = false);
    void run();
    void handleInputs();
    void draw();
    void checkTime();
};
#endif