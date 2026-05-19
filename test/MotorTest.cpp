#include "MotorTest.h"



/*!
 * @brief Constructor for the MotorController class.
 */
MotorTest::MotorTest() {}

/*!
 * @brief Destructor for the MotorController class.
 */
MotorTest::~MotorTest() {
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
}

/*!
 * @brief Drives the robot forward at a specified speed.
 * @param speed The speed at which to drive forward.
 */

void MotorTest::forwardLeft(int16_t speed) {
    motors.setLeftSpeed(speed);
}

/*!
 * @brief Stops the robot.
 */
void MotorTest::stop() {
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);
}

