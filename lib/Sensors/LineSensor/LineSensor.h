#pragma once
#include <Zumo32U4.h>

#define NUM_SENSORS 5

// Tune these by calling getLineReflectance() while over each color
#define THRESHOLD_GREEN 280
#define THRESHOLD_BROWN 430
#define THRESHOLD_GREY  730
#define THRESHOLD_LINE  30  // anything below this is just floor

#define COLOR_DEBOUNCE 7 // consecutive readings before color is confirmed

enum class LineColor { UNKNOWN, GREEN, GREY, BROWN };

class LineSensor {
    public:
        void initialize();
        void calibrate();
        int16_t readLine();
        LineColor detectColor();
        LineColor detectLeftColor();
        LineColor detectRightColor();
        LineColor detectGrijs();
        uint16_t getLineReflectance();
        uint16_t getLeftReflectance();
        uint16_t getMiddleReflectance();
        uint16_t getRightReflectance();
    private:
        Zumo32U4LineSensors sensors;
        unsigned int sensorValues[NUM_SENSORS];
        LineColor colorFromReflectance(uint16_t r);
        LineColor debouncedColor(uint16_t r);
        LineColor _pendingColor  = LineColor::UNKNOWN;
        LineColor _confirmedColor = LineColor::UNKNOWN;
        uint8_t   _pendingCount  = 0;
};
