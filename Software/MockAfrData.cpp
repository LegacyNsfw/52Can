#include <Arduino.h>
#include "Constants.h"
#include "MockAfrData.h"

void MockAfrData::initialize() {
    value1 = MIN_LAMBDA;
    rise1 = 1;

    value2 = MAX_LAMBDA;
    rise2 = 1;

    delta = (MAX_LAMBDA - MIN_LAMBDA) / 150;
}

void MockAfrData::loop() {
    // Animate value1
    if (value1 >= MAX_LAMBDA) {
        rise1 = 0;
    } else if (value1 <= MIN_LAMBDA) {
        rise1 = 1;
    }

    if (rise1 == 1) {
        value1 += delta;
    } else {
        value1 -= delta;
    }

    // Animate value2
    if (value2 >= MAX_LAMBDA) {
        rise2 = 0;
    } else if (value2 <= MIN_LAMBDA) {
        rise2 = 1;
    }

    if (rise2 == 1) {
        value2 += delta;
    } else {
        value2 -= delta;
    }
}