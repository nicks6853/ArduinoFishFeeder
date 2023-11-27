#include "FishFeeder.h"

FishFeeder fishFeeder;

void setup() {
    Serial.begin(115200);
    fishFeeder.begin();
}

void loop() { fishFeeder.run(); }