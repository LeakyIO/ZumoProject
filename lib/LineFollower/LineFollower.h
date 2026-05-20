#include <Arduino.h>
#include "Zumo32U4LineSensors.h"
#include "MotorController.h"

class LineFollower {
    private:
        static Zumo32U4LineSensors lineSensors;
        static MotorController motorController;

    public:
        LineFollower();

        ~LineFollower();

        void followLine();
        void searchLine();

        bool detected();
};