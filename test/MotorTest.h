#pragma once

#include <stdint.h>
#include <Arduino.h>
#include <Zumo32U4Motors.h>
#include <Zumo32U4Encoders.h>

class MotorController {
    private:
        static Zumo32U4Motors motors;
        static Zumo32U4Encoders encoders;

    public:

        /*!
         * @brief Constructor for the MotorController class.
         */
        MotorTest();

        /*!
         * @brief Destructor for the MotorController class.
         */
        ~MotorTest();


        void leftForward(int16_t speed);
    
        void leftBackward(int16_t speed);

        void rightForward(int16_t speed);

        void rightBackward(int16_t speed);

        /*!
         * @brief Stops the robot.
         */
        void stop();


    };