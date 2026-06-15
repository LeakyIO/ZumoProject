#pragma once
#include <Zumo32U4.h>


#define NUM_SENSORS 5

class LineSensor {
    public:
        LineSensor();
        ~LineSensor();
        void initialize();
        void calibrate();
        // void groeneLijn();
        // void bruineLijn();
        // void groeneLijn();
        // void grijzeLijn();
        uint16_t readLine();
        void getSensorValues(unsigned int *outSensorValues);
        unsigned int getMaxSensorValue();

        void readCalibrated();
        unsigned int sensorValues[NUM_SENSORS];

    private:
        Zumo32U4LineSensors sensors;
};