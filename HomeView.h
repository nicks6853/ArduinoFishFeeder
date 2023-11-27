#ifndef HOME_VIEW_H
#define HOME_VIEW_H

#include "Definitions.h"
#include "View.h"

class HomeView : public View {
   public:
    HomeView(FishFeeder* fishFeederPtr);
    void run();
    void handleInputs();
    void draw();
};
#endif