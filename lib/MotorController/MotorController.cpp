#include <Arduino.h>
#include "MotorController.h"
#include <Zumo32U4Motors.h>
#include <Zumo32U4Encoders.h>

static Zumo32U4Motors motors;
static Zumo32U4Encoders encoders;

MotorController::MotorController() {}

MotorController::~MotorController() {
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
}

void MotorController::forward(int16_t speed) {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
}

void MotorController::backward(int16_t speed) {
    motors.setLeftSpeed(-speed);
    motors.setRightSpeed(-speed);
}

void MotorController::turnLeft(int16_t speed) {
    motors.setLeftSpeed(-speed);
    motors.setRightSpeed(speed);
}

void MotorController::turnRight(int16_t speed) {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(-speed);
}

void MotorController::stop() {
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);
}


void MotorController::driveRevolutions(float revolutions, int16_t speed) {
  
   const int32_t ticksPerRev = 900;
   int32_t target  = (int32_t)(revolutions * ticksPerRev);
  
  encoders.getCountsAndResetLeft();
  encoders.getCountsAndResetRight();

  forward(speed);

  while (true) {

    int32_t left = labs(encoders.getCountsLeft());
    int32_t right = labs(encoders.getCountsRight());

    Serial.print("L: ");
    Serial.print(left);
    Serial.print("  R: ");
    Serial.println(right);
    
    if (left >= target && right >= target) break;

    // nudge the lagging wheel
    int16_t leftSpeed  = (left  < right) ? speed + 20 : speed;
    int16_t rightSpeed = (right < left)  ? speed + 20 : speed;

    motors.setLeftSpeed(leftSpeed);
    motors.setRightSpeed(rightSpeed);
  }
}

