#include <Arduino.h>
#include "Zumo32U4LineSensors.h"

class LineFollowerTest {
    private:
        static Zumo32U4LineSensors lineSensors;

    public:
        LineFollowerTest();

        ~LineFollowerTest();

        void followLine();
        void searchLine();

        bool detected();
};