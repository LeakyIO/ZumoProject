#pragma once
#include <MotorController.h>
#include <LineSensor.h>

class LineFollower {
    public:
        LineFollower(MotorController& motors, LineSensor& sensor);
        void follow();
        void rechtdoorOverKruising();
        void doeRechtsAfslag();
    private:
        MotorController& motors;
        LineSensor& sensor;
        int16_t lastError = 0;
        bool draaiRechts;
};