// #include <Arduino.h>
// #include <MotorController.h>
// #include <Encoder.h>
// #include <Zumo32U4Buttons.h>


// Zumo32U4ButtonA buttonA;
// Zumo32U4ButtonB buttonB;

// MotorController motors;
// Encoder encoder;

// unsigned long stopTime = 0;
// bool running = false;

// void setup() {
//     Serial.begin(9600);
//     encoder.reset();
// }

// void loop() {
//     if (buttonA.isPressed() && !running) {
//         delay(500);
//         encoder.reset();
//         motors.setLeftSpeed(200);
//         motors.setRightSpeed(200);
//         stopTime = millis() + 3000;
//         running = true;
//     }

//     if (running && millis() >= stopTime) {
//         motors.stop();
//         running = false;
//     }

//     if (running) {
//         encoder.printCounts();
//     }

//     if (buttonB.isPressed()) {
//         delay(200);
//         running = true;
//         motors.driveRevolutions(5);
        
//     }
// }
