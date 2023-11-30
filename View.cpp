#include "View.h"

#include "FishFeeder.h"

View::View(FishFeeder* fishFeederPtr, bool shouldPause) {
    fishFeeder = fishFeederPtr;
    gotoView = NULL;
    this->shouldPause = shouldPause;
}

View* View::getGotoView() { return gotoView; }