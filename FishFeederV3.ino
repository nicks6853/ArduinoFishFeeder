#include <RotaryEncoder.h>

#include "FishFeeder.h"

FishFeeder fishFeeder;
RotaryEncoder* encoder = NULL;

IRAM_ATTR void checkPosition() { encoder->tick(); }

void setup() {
    Serial.begin(115200);

    // Initialize Rotary Encoder
    encoder = new RotaryEncoder(ROTARY_CLK_PIN, ROTARY_DT_PIN,
                                RotaryEncoder::LatchMode::FOUR3);

    attachInterrupt(ROTARY_CLK_PIN, checkPosition, CHANGE);
    attachInterrupt(ROTARY_DT_PIN, checkPosition, CHANGE);
    pinMode(ROTARY_SW_PIN, INPUT_PULLUP);

    fishFeeder.setRotaryEncoder(encoder);
    fishFeeder.begin();
}

void loop() { fishFeeder.run(); }