#include <Arduino.h>
#include "Zumo32U4LineSensors.h"

class LineFollower {
    private:
        static Zumo32U4LineSensors lineSensors;

    public:
        LineFollower();

        ~LineFollower();

        void followLine();
        void searchLine();

        bool detected();
};