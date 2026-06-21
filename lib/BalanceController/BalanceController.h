#pragma once

#include <Zumo32U4.h>
#include <MotorController.h>

// extern Zumo32U4Motors motors;
extern MotorController motors;
extern Zumo32U4Encoders encoders;

static const float ENCODER_COUNTS_PER_WHEEL_REV = 909.7;

static const float WHEEL_DIAMETER_MM = 38.0;

void runCalibrationSweep();

void runActiveBalance();

extern bool Eenkeer;