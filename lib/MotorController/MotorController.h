#pragma once

#include <stdint.h>




class MotorController {
public:

    /*!
     * @brief Constructor for the MotorController class.
     */
    MotorController();

    /*!
     * @brief Destructor for the MotorController class.
     */
    ~MotorController();

    /*!
     * @brief Drives the robot forward at a specified speed.
     * @param speed The speed at which to drive forward.
     */
    void forward(int16_t speed);

    /*!
     * @brief Drives the robot backward at a specified speed.
     * @param speed The speed at which to drive backward.
     */
    void backward(int16_t speed);

    /*!
     * @brief Turns the robot left at a specified speed.
     * @param speed The speed at which to turn left.
     */
    void turnLeft(int16_t speed);

    /*!
     * @brief Turns the robot right at a specified speed.
     * @param speed The speed at which to turn right.
     */
    void turnRight(int16_t speed);

    /*!
     * @brief Stops the robot.
     */
    void stop();

    /*!
     * @brief Drives the robot for a specified number of revolutions at a specified speed.
     * @param revolutions The number of revolutions to drive.
     * @param speed The speed at which to drive.
     */
    void driveRevolutions(float revolutions, int16_t speed);


};