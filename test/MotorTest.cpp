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

void MotorTest::setLeftSpeed(int16_t speed) {
    motors.setLeftSpeed(speed);
}

void MotorTest::setRightSpeed(int16_t speed) {
    motors.setRightSpeed(speed);
}

/*!
 * @brief Stops the robot.
 */
void MotorTest::stop() {
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);
}

