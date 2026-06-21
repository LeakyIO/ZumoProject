#pragma once

#include <Zumo32U4.h>

extern Zumo32U4IMU imu;

extern float pitchAngleDegrees;

extern float pitchRateDegreesPerSecond;

void tiltSensorSetup();

void tiltSensorUpdate();

float pitchAngleDegrees = 0.0;
float pitchRateDegreesPerSecond = 0.0;

static float gyroYOffset = 0.0;

static float accelAngleOffsetDegrees = 0.0;

static uint32_t lastUpdateMicros = 0;

static const float GYRO_DPS_PER_DIGIT = 0.07;

static const float FILTER_GYRO_WEIGHT = 0.98;