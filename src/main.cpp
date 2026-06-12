#include <Arduino.h>
#include <MotorController.h>
#include <LineSensor.h>
#include <Zumo32U4Buttons.h>
#include <Zumo32U4Buzzer.h>
#include <LineFollower.h>



Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4Buzzer buzzer;
MotorController motors;
LineSensor lineSensor;
LineFollower lineFollower(motors, lineSensor);

bool following = false;


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
  }
  motors.setSpeeds(0, 0);
}

void setup(){

    Serial.begin(9600);

    lineSensor.initialize();
    
    //buzzer.play("T90 L8 O3 aaa f16>c16 a f16>c16 a");

    calibrateLineSensors();

}


void loop() {
    if (buttonB.isPressed()) following = true;
    if (buttonA.isPressed()) {
        following = false;
        motors.stop();
    }

    if (following) lineFollower.follow();
}
 