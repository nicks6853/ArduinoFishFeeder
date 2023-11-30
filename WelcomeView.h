#ifndef WELCOME_VIEW_H
#define WELCOME_VIEW_H

#include "Definitions.h"
#include "HomeView.h"
#include "View.h"

class WelcomeView : public View {
   public:
    WelcomeView(FishFeeder* fishFeeder, bool shouldPause = false);
    void run();
    void handleInputs();
    void draw();
};
#endif