#pragma once

#include <stdint.h>


class MotorController {
public:

    MotorController();

    ~MotorController();

    void forward(int16_t speed);

    void backward(int16_t speed);

    void turnLeft(int16_t speed);

    void turnRight(int16_t speed);

    void stop();

    void driveRevolutions(float revolutions, int16_t speed);
    

};