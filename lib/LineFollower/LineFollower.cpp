#include "LineFollower.h"

const uint16_t maxSpeed = 200;

LineFollower::LineFollower(MotorController& motors, LineSensor& sensor)
    : motors(motors), sensor(sensor) {}

void LineFollower::follow() {
    int16_t position = sensor.readLine();
    int16_t error = position - 2000;
    int16_t speedDifference = error / 4 + 6 * (error - lastError);
    lastError = error;

    int16_t leftSpeed = constrain((int16_t)maxSpeed + speedDifference, 0, (int16_t)maxSpeed);
    int16_t rightSpeed = constrain((int16_t)maxSpeed - speedDifference, 0, (int16_t)maxSpeed);

    motors.setSpeeds(leftSpeed, rightSpeed);
}