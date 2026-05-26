#include "MotorController.h"

#define TICKS_PER_REV 1195

MotorController::MotorController() {}

MotorController::~MotorController() {
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
}

void MotorController::setLeftSpeed(int16_t speed) {
    motors.setLeftSpeed(speed);
}

void MotorController::setRightSpeed(int16_t speed) {
    motors.setRightSpeed(speed);
}

void MotorController::setSpeeds(int16_t leftSpeed, int16_t rightSpeed) {
    motors.setSpeeds(leftSpeed, rightSpeed);
}

void MotorController::stop() {
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);
}


void MotorController::driveRevolutions(float revs) {
    encoder.reset();
    setLeftSpeed(200);
    setRightSpeed(200);
    while (abs(encoder.getCountLeft()) < revs * TICKS_PER_REV) {
        encoder.printCounts();
        delay(50);
    }
    stop();
}