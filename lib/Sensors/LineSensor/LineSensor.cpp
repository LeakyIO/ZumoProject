#include "LineSensor.h"


void LineSensor::calibrate() {
    sensors.calibrate();
}

void LineSensor::initialize() {
    sensors.initFiveSensors();
}

int16_t LineSensor::readLine() {
    return sensors.readLine(sensorValues);
}