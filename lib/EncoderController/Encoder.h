#pragma once
#include <Zumo32U4Encoders.h>
#include <Arduino.h>


class Encoder {
    private:
        Zumo32U4Encoders encoders;

    public:
        long getCountLeft();
        long getCountRight();
        int getDrift();
        void reset();
        void printCounts();

};