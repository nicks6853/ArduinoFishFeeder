#ifndef VIEW_H
#define VIEW_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

class FishFeeder;  // Forward declaration

class View {
   protected:
    View* gotoView;
    bool shouldPause;
    FishFeeder* fishFeeder;

   public:
    View(FishFeeder* fishFeederPtr, bool shouldPause = false);
    View* getGotoView();

    /**
     * Perform all actions for each cycle for this view
     */
    virtual void run() = 0;

    /**
     * Draw the graphics to the display
     */
    virtual void draw() = 0;

    /**
     * Check inputs and perform necessary actions
     */
    virtual void handleInputs() = 0;
};
#endif
