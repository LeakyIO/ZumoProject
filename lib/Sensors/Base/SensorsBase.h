#include <Wire.h>
#include <Zumo32U4.h>
#include "Arduino.h"

#ifndef SENSORSBASE_H
#define SENSORSBASE_H

class SensorsBase {

    protected:
        bool isCalibrated;
        bool isEnabled;

    public:
        SensorsBase();
        virtual ~SensorsBase();

        bool initialize();
        virtual void read() = 0; // Pure virtual function to be implemented by derived classes
        virtual void calibrate();
        bool isReady() const;
};

#endif // SENSORSBASE_H 
