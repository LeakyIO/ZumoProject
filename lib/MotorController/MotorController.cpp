#include "MotorController.h"




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

void MotorController::stop() {
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);
}

