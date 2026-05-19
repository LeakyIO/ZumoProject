#pragma once

#include <stdint.h>
#include <Arduino.h>
#include <Zumo32U4Motors.h>
#include <Zumo32U4Encoders.h>

class MotorTest {
    private:
        static Zumo32U4Motors motors;
        static Zumo32U4Encoders encoders;

    public:  

        MotorTest();

        ~MotorTest();


        void setLeftSpeed(int16_t speed);
        
        void setRightSpeed(int16_t speed);

        /*!
         * @brief Stops the robot.
         */
        void stop();


    };