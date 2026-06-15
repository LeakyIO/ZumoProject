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

// unsigned int sensorValues[5];


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


}


void loop() {
    if (buttonB.getSingleDebouncedPress()){
        Serial.println("B");
        calibrateLineSensors();
        
    }
    
    if (buttonA.getSingleDebouncedPress()) {
        Serial.println("A");
        
        following = false;
        motors.stop();
    }
    if (buttonC.getSingleDebouncedPress()) {
        Serial.println("C");
        following = true;
        // Serial.println(lineSensor.readLine());
        // lineSensor.getSensorValues(sensorValues);
        //  Serial.println(String(lineSensor.readLine()) + '|' + sensorValues[0] + ',' +
        //            sensorValues[1] + ',' + sensorValues[2] + ',' +
        //            sensorValues[3] + ',' + sensorValues[4]);
}
       
    
    if (following) lineFollower.follow();
    
static unsigned long lastPrint = 0;
if (millis() - lastPrint >= 1000) {
    lastPrint = millis();
    // lineSensor.getSensorValues(sensorValues);
    Serial.println(String(lineSensor.readLine()) + '|' + lineSensor.sensorValues[0] + ',' +
                   lineSensor.sensorValues[1] + ',' + lineSensor.sensorValues[2] + ',' +
                   lineSensor.sensorValues[3] + ',' + lineSensor.sensorValues[4]);
}
            }
 