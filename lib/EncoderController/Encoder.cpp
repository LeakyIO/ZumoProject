#include "Encoder.h"

void Encoder::reset() {
    encoders.getCountsAndResetLeft();
    encoders.getCountsAndResetRight();
}

long Encoder::getCountLeft() {
    return encoders.getCountsLeft();
}

long Encoder::getCountRight() {
    return encoders.getCountsRight();
}

int Encoder::getDrift() {
    return encoders.getCountsLeft() - encoders.getCountsRight();
}   


void Encoder::printCounts() {
    Serial.print("L: ");
    Serial.print(getCountLeft());
    Serial.print(" R: ");
    Serial.print(getCountRight());
    Serial.print("Drift: ");
    Serial.println(getDrift());
}

