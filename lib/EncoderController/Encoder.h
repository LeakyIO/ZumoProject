#pragma once
#include <Zumo32U4Encoders.h>
#include <Arduino.h>


class Encoder {
    private:
        // We gebruiken de Zumo32U4Encoders klasse van Pololu, maar deze geeft slechts 16-bit getallen terug die kunnen over- en onderlopen.
        Zumo32U4Encoders encoders;

    public:
        long getCountLeft();
        long getCountRight();
        int getDrift();
        void reset();
        void printCounts();

};