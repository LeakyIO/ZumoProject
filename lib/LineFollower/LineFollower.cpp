
#include "LineFollower.h"


LineFollower::LineFollower() {}

LineFollower::~LineFollower() {

}

void LineFollower::followLine() {
    lineSensors.read();
    uint16_t sensorValues[5];
    lineSensors.getSensorValues(sensorValues);
    // Implement line following logic based on sensor values
}

void LineFollower::searchLine() {
    // Implement logic to search for the line when it is lost
}



