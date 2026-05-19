#include <Arduino.h>
#include <Zumo32U4Buttons.h>
#include "MotorController.h"

// Create instances of the MotorController and the buttons.
MotorController motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;

// The setup function runs once when you press reset or power the board
void setup(){
    Serial.begin(9600);
}


void loop() {

    // Check if button A is pressed to drive forward, and stop the robot if it is not pressed.

    if (buttonA.getSingleDebouncedPress()) {
        delay(500); // debounce delay
        motors.driveRevolutions(8.0, 200);
    } else {
        motors.stop();
    }


    // Check if button B is pressed to drive backward, and stop the robot if it is not pressed.
    if (buttonB.getSingleDebouncedPress()) {
        delay(500); // debounce delay
        motors.driveRevolutions(8.0, -200);
    } else {
        motors.stop();
    }
}