#include <Arduino.h>
#include "MotorController.h"
#include <Zumo32U4Motors.h>
#include <Zumo32U4Encoders.h>

static Zumo32U4Motors motors;
static Zumo32U4Encoders encoders;

/*!
 * @brief Constructor for the MotorController class.
 */
MotorController::MotorController() {}

/*!
 * @brief Destructor for the MotorController class.
 */
MotorController::~MotorController() {
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
}

/*!
 * @brief Drives the robot forward at a specified speed.
 * @param speed The speed at which to drive forward.
 */

void MotorController::forward(int16_t speed) {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
}
/*!
 * @brief Drives the robot backward at a specified speed.
 * @param speed The speed at which to drive backward.
 */
void MotorController::backward(int16_t speed) {
    motors.setLeftSpeed(-speed);
    motors.setRightSpeed(-speed);
}

/*!
 * @brief Turns the robot left at a specified speed.
 * @param speed The speed at which to turn left.
 */
void MotorController::turnLeft(int16_t speed) {
    motors.setLeftSpeed(-speed);
    motors.setRightSpeed(speed);
}

/*!
 * @brief Turns the robot right at a specified speed.
 * @param speed The speed at which to turn right.
 */
void MotorController::turnRight(int16_t speed) {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(-speed);
}

/*!
 * @brief Stops the robot.
 */
void MotorController::stop() {
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);
}

/*!
 * @brief Drives the robot for a specified number of revolutions at a specified speed.
 * @param revolutions The number of revolutions to drive.
 * @param speed The speed at which to drive.
 */
void MotorController::driveRevolutions(float revolutions, int16_t speed) {
  
  // Calculate the target number of encoder ticks based on the desired number of revolutions.
  const int32_t ticksPerRev = 1200;
  int32_t target  = (int32_t)(revolutions * ticksPerRev);
  
  // Reset the encoder counts to start fresh for this movement.
  encoders.getCountsAndResetLeft();
  encoders.getCountsAndResetRight();

  // Start driving forward at the specified speed.
  forward(speed);

  while (true) {

    // Get the absolute value of the encoder counts for both wheels.
    int32_t left = labs(encoders.getCountsLeft());
    int32_t right = labs(encoders.getCountsRight());

    // Print the current number of revolutions for debugging purposes.
    Serial.print("L: ");
    Serial.print((float)left / ticksPerRev);
    Serial.print("  R: ");
    Serial.println((float)right / ticksPerRev);

    // Check if both wheels have reached the target number of revolutions.
    if (left >= target && right >= target) break;

    // nudge the lagging wheel
    int16_t leftSpeed  = (left  < right) ? speed + 20 : speed;
    int16_t rightSpeed = (right < left)  ? speed + 20 : speed;

    // Set the motor speeds to drive the robot forward, with a nudge to the lagging wheel.
    motors.setLeftSpeed(leftSpeed);
    motors.setRightSpeed(rightSpeed);
  }
}

