#include "TiltSensor.h"
#include <Arduino.h>
#include <math.h>





void tiltSensorUpdate()
{

  uint32_t currentMicros = micros();
  float dt = (float)(currentMicros - lastUpdateMicros) / 1000000.0;
  lastUpdateMicros = currentMicros;

  imu.readGyro();

  float gyroYRaw = (float)imu.g.y - gyroYOffset;

  pitchRateDegreesPerSecond = gyroYRaw * GYRO_DPS_PER_DIGIT;

  float gyroAngleEstimate = pitchAngleDegrees + (pitchRateDegreesPerSecond * dt);

  imu.readAcc();
  float accelAngleEstimate = (atan2((float)imu.a.x, (float)imu.a.z) * 180.0 / PI)
                            - accelAngleOffsetDegrees;

  pitchAngleDegrees = (FILTER_GYRO_WEIGHT * gyroAngleEstimate)
                     + ((1.0 - FILTER_GYRO_WEIGHT) * accelAngleEstimate);
}