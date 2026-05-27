#pragma once

#include <stdint.h>
#include <Arduino.h>
#include <Zumo32U4Motors.h>
#include "Encoder.h"

class MotorController {
    private:
        Zumo32U4Motors motors;
        Encoder encoder;

    public:  

        MotorController();

        ~MotorController();

        void setLeftSpeed(int16_t speed);
        
        void setRightSpeed(int16_t speed);

        void setSpeeds(int16_t leftSpeed, int16_t rightSpeed);

        void stop();

        void driveRevolutions(float revs);

    };