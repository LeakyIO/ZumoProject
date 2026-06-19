#include "LineFollower.h"

LineFollower::LineFollower(MotorController& motors, LineSensor& sensor)
    : motors(motors), sensor(sensor) {}

int16_t LineFollower::greenSpeed() {
    return (sensor.detectLeftColor() == LineColor::GREEN || sensor.detectRightColor() == LineColor::GREEN || sensor.detectColor() == LineColor::GREEN) ? maxSpeed / 2 : maxSpeed;
}

void LineFollower::follow() {
    int16_t position = sensor.readLine();

    if (sensor.getLineReflectance() == 0) {
        if (abs(lastError) < 500)
            motors.setSpeeds(maxSpeed / 2, maxSpeed / 2);
        else if (lastError > 0)
            motors.setSpeeds(maxSpeed / 2, -(maxSpeed / 2));
        else
            motors.setSpeeds(-(maxSpeed / 2), maxSpeed / 2);
        return;
    }

    if (sensor.getMiddleReflectance() < THRESHOLD_LINE) {
        if (sensor.getLeftReflectance() > THRESHOLD_LINE) {
            while (sensor.getMiddleReflectance() < THRESHOLD_LINE) {
                motors.setSpeeds(-(maxSpeed / 2), maxSpeed / 2);
                sensor.readLine();
            }
            lastError = 0;
            return;
        }
        if (sensor.getRightReflectance() > THRESHOLD_LINE) {
            while (sensor.getMiddleReflectance() < THRESHOLD_LINE) {
                motors.setSpeeds(maxSpeed / 2, -(maxSpeed / 2));
                sensor.readLine();
            }
            lastError = 0;
            return;
        }
    }

    int16_t error = position - 2000;
    int16_t speed = constrain(greenSpeed() - abs(error) / 9, 200, greenSpeed());
    int16_t speedDifference = error / 2 + 7 * (error - lastError);
    lastError = error;

    int16_t leftSpeed  = constrain(speed + speedDifference, -400, speed);
    int16_t rightSpeed = constrain(speed - speedDifference, -400, speed);
    motors.setSpeeds(leftSpeed, rightSpeed);
}
