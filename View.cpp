#include "View.h"

#include "FishFeeder.h"

View::View(FishFeeder* fishFeederPtr) {
    fishFeeder = fishFeederPtr;
    gotoView = NULL;
}

View* View::getGotoView() { return gotoView; }