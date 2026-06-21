#include "BalanceController.h"
#include "TiltSensor.h"
#include <Arduino.h>
#include <math.h>

static const float SWEEP_TOLERANCE_DEGREES = 5.7;
static const int16_t SWEEP_CREEP_SPEED = 67;
static const float SWEEP_STARTING_STEP_MM = 1;
static const float SWEEP_MINIMUM_STEP_MM = 0.05;
static const int SWEEP_SETTLE_TIME_MS = 500;
static const int SWEEP_MAX_ITERATIONS = 500;

static const int BALANCE_CONFIRM_TIME_MS = 1500;

static const float BALANCE_DEADBAND_DEGREES = 0.3;
static const float BALANCE_KP = 18.0;
static const int16_t BALANCE_MAX_SPEED = 150;

static float mmToEncoderCounts(float mm)
{
  float wheelCircumferenceMm = PI * WHEEL_DIAMETER_MM;
  return (mm / wheelCircumferenceMm) * ENCODER_COUNTS_PER_WHEEL_REV;
}

static void creepByEncoderCounts(float targetCounts, int direction)
{

  encoders.getCountsAndResetLeft();
  encoders.getCountsAndResetRight();

  float countsSoFar = 0.0;
  int16_t speed = (int16_t)(SWEEP_CREEP_SPEED * direction);

  motors.setSpeeds(speed, speed);

  while (countsSoFar < targetCounts)
  {

    tiltSensorUpdate();

    int16_t left = encoders.getCountsAndResetLeft();
    int16_t right = encoders.getCountsAndResetRight();

    float counted = ((float)left + (float)right) / 2.0;
    countsSoFar += fabs(counted);
  }

  motors.setSpeeds(0, 0);
}

static void settleAndUpdateTilt(int totalMilliseconds)
{
  const int sliceMs = 10;
  int elapsed = 0;

  while (elapsed < totalMilliseconds)
  {
    tiltSensorUpdate();
    delay(sliceMs);
    elapsed += sliceMs;
  }
}



static void celebrateBalancePoint()
{
  Serial.println(F("Standing still..."));
  motors.setSpeeds(0, 0);
  Eenkeer = false; 
  return;

  while (true)
  {

  }
}



static bool isBalancePointConfirmed()
{
  Serial.println(F("Checking if this is a real, stable balance point..."));

  const int sliceMs = 10;
  int withinToleranceMs = 0;

  while (withinToleranceMs < BALANCE_CONFIRM_TIME_MS)
  {
    tiltSensorUpdate();

    if (fabs(pitchAngleDegrees) <= SWEEP_TOLERANCE_DEGREES)
    {

      withinToleranceMs += sliceMs;
    }
    else
    {

      Serial.println(F("Drifted out of tolerance - not stable yet."));
      return false;
    }

    delay(sliceMs);
  }

  Serial.println(F("Confirmed! Stable for 3 full seconds."));
  return true;
}

void runCalibrationSweep()
{
  Serial.println(F("Starting calibration sweep (encoder binary search)..."));

  float stepSizeMm = SWEEP_STARTING_STEP_MM;

  tiltSensorUpdate();
  bool previousSignWasPositive = (pitchAngleDegrees >= 0.0);

  int currentDirection = previousSignWasPositive ? 1 : -1;

  Serial.print(F("Starting pitchAngleDegrees = "));
  Serial.print(pitchAngleDegrees);
  Serial.print(F("  starting direction = "));
  Serial.println(currentDirection);

  for (int iteration = 0; iteration < SWEEP_MAX_ITERATIONS; iteration++)
  {

    if (fabs(pitchAngleDegrees) <= SWEEP_TOLERANCE_DEGREES)
    {
      if (isBalancePointConfirmed())
      {
        Serial.println(F("Balance point found!"));
        celebrateBalancePoint();
        return;
      }

    }

    if (stepSizeMm < SWEEP_MINIMUM_STEP_MM)
    {
      Serial.println(F("Step size below minimum. Balance point found!"));
      celebrateBalancePoint();
      return;
    }

    Serial.print(F("Iteration "));
    Serial.print(iteration);
    Serial.print(F("  direction = "));
    Serial.print(currentDirection);
    Serial.print(F("  stepSizeMm = "));
    Serial.println(stepSizeMm);

    float targetCounts = mmToEncoderCounts(stepSizeMm);
    creepByEncoderCounts(targetCounts, currentDirection);

    settleAndUpdateTilt(SWEEP_SETTLE_TIME_MS);

    tiltSensorUpdate();

    Serial.print(F("  -> pitchAngleDegrees = "));
    Serial.println(pitchAngleDegrees);

    bool currentSignIsPositive = (pitchAngleDegrees >= 0.0);

    if (currentSignIsPositive != previousSignWasPositive)
    {

      stepSizeMm = stepSizeMm / 2.0;
      currentDirection = -currentDirection;
      Serial.println(F("  -> direction flipped! Halving step size."));
    }
    else
    {

      Serial.println(F("  -> no flip yet, continuing the same way."));
    }

    previousSignWasPositive = currentSignIsPositive;
  }

  Serial.println(F("Sweep finished WITHOUT reaching tolerance."));
  Serial.println(F("Consider checking SWEEP_MAX_ITERATIONS or starting position."));
  motors.setSpeeds(0, 0);
}



void runActiveBalance()
{

  tiltSensorUpdate();

  float error = pitchAngleDegrees - 0.0;

  if (fabs(error) <= BALANCE_DEADBAND_DEGREES)
  {
    motors.setSpeeds(0, 0);
    return;
  }

  float speed = error * BALANCE_KP;

  if (speed > BALANCE_MAX_SPEED)
  {
    speed = BALANCE_MAX_SPEED;
  }
  if (speed < -BALANCE_MAX_SPEED)
  {
    speed = -BALANCE_MAX_SPEED;
  }

  motors.setSpeeds((int16_t)speed, (int16_t)speed);
}