#include "LineSensor.h"


LineSensor::LineSensor(): sensorValues({0, 0, 0, 0, 0}){
}

LineSensor::~LineSensor(){}

void LineSensor::calibrate() {
    sensors.calibrate();
}

void LineSensor::initialize() {
    sensors.initFiveSensors();
}

void LineSensor::getSensorValues(unsigned int *outSensorValues) {
    for (uint8_t i = 0; i < 5; i++){
    outSensorValues[i] = sensorValues[i];
    }
}

unsigned int LineSensor::getMaxSensorValue() {
    unsigned int max = 0;
    for (uint8_t i = 0; i < 5; i++) {
        if (sensorValues[i]> max) {
            max = sensorValues[i];
        }
    }
    return max;
}

uint16_t LineSensor::readLine() {
    return sensors.readLine(sensorValues);
}

void LineSensor::readCalibrated(){
    sensors.readCalibrated(sensorValues);
}

// void LineSensor::bruineLijn(){
//     if(sensorValues > 0 && sensorValues < 5){

//     }

// }
// void LineSensor::groeneLijn(){
//     if(sensorValues > 0 && sensorValues < 5){

//     }

// }

// void LineSensor::grijzeLijn(){
//     if(sensorValues > 5 && sensorValues < 10){

//     }



