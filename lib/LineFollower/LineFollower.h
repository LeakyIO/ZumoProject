#pragma once
#include <MotorController.h>
#include <LineSensor.h>

class LineFollower {
    public:
        LineFollower(MotorController& motors, LineSensor& sensor);
        void follow();
    private:
        MotorController& motors;
        LineSensor& sensor;
        int16_t lastError = 0;
};