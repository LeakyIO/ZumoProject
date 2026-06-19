#include <Arduino.h>
#include <MotorController.h>
#include <LineSensor.h>
#include <Zumo32U4Buttons.h>
#include <Zumo32U4Buzzer.h>
#include <LineFollower.h>



Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4Buzzer buzzer;
MotorController motors;
LineSensor lineSensor;
LineFollower lineFollower(motors, lineSensor);

bool following = false;
bool printing = false;

void calibrateLineSensors(){
    delay(1000);
    for(uint16_t i = 0; i < 120; i++){
        if (i > 30 && i <= 90){
            motors.setSpeeds(-200, 200);
        }
        else {
            motors.setSpeeds(200, -200);
        }
    lineSensor.calibrate();
    delay(10);
  }
  motors.setSpeeds(0, 0);
}


void setup(){
    Serial.begin(9600);
    Serial1.begin(9600);
    //while (!Serial);
    //delay(500);
    lineSensor.initialize();
    Serial.println("Press A to calibrate line sensors");
    //buzzer.play("T90 L8 O3 aaa f16>c16 a f16>c16 a");
    while (!buttonA.isPressed());
    calibrateLineSensors();
    Serial.println("Calibration complete. Press B to start following the line, A to stop, and C to toggle sensor printing.");

}


void loop() {
    if (buttonB.isPressed()) {
        delay(300);
        following = true;
    }
    if (buttonA.isPressed()) {
        following = false;
        motors.stop();
    }
    if (buttonC.isPressed()) {
        delay(300);
        printing = !printing;
    }

    if (following) lineFollower.follow();

    if (printing) {
        lineSensor.readLine();
        Serial1.print("L:");  Serial1.print(lineSensor.getLeftReflectance());
        Serial1.print(" M:"); Serial1.print(lineSensor.getMiddleReflectance());
        Serial1.print(" R:"); Serial1.println(lineSensor.getRightReflectance());
    }
}
