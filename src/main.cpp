#include <Arduino.h>
#include <Zumo32U4Buttons.h>
#include "MotorController.h"

MotorController motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;

void setup(){
    Serial.begin(9600);
}

void loop() {

    if (buttonA.getSingleDebouncedPress()) {
        delay(500); // debounce delay
        motors.driveRevolutions(2.0, 200);
    } else {
        motors.stop();
    }
    if (buttonB.getSingleDebouncedPress()) {
        delay(500); // debounce delay
        motors.driveRevolutions(2.0, -200);
        delay(1000);
    } else {
        motors.stop();
    }



    if (buttonC.getSingleDebouncedPress()) {
        delay(500); // debounce delay

        motors.forward(400);
        delay(1000);
        motors.turnLeft(200);
        delay(600);
        motors.forward(400);
        delay(1000);
        motors.turnLeft(200);
        delay(600);
        motors.forward(400);
        delay(1000);
        motors.turnLeft(200);
        delay(600);
        motors.forward(400);
        delay(1000);
        motors.turnLeft(200);
        delay(600);
       
    } else {
        motors.stop();
    }
}