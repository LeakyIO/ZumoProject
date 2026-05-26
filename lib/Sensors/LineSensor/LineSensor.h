#pragma once
#include <Zumo32U4.h>

#define NUM_SENSORS 5

class LineSensor {
    public:

        void initialize();
        void calibrate();
        int16_t readLine();
    private:
        Zumo32U4LineSensors sensors;
        unsigned int sensorValues[NUM_SENSORS];
};