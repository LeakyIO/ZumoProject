#pragma once

#include <stdint.h>
#include <Arduino.h>
#include <Zumo32U4Motors.h>

class MotorController {
    private:
        Zumo32U4Motors motors;

    public:  

        MotorController();

        ~MotorController();

        void setLeftSpeed(int16_t speed);
        
        void setRightSpeed(int16_t speed);

        void stop();


    };