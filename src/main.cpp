#include <Arduino.h>
#include <MotorController.h>
#include <LineSensor.h>
#include <Zumo32U4Buttons.h>
#include <Zumo32U4Buzzer.h>
#include <LineFollower.h>
#include <Zumo32U4.h>
#include "TiltSensor.h"
#include <BalanceController.h>
#include <Wire.h>
#include "TiltSensor.h"
#include <Arduino.h>
#include <math.h>



Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4Buzzer buzzer;
LineSensor lineSensor;
Zumo32U4IMU imu;
Zumo32U4Encoders encoders;
MotorController motors;

LineFollower lineFollower(motors, lineSensor);

bool following = false;
bool printing = false;
bool Eenkeer = true;

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

void tiltSensorSetup()
{

  Serial.println(F("Calibrating gyro. Keep the robot still and level!"));
  delay(500);

  const int numCalibrationReadings = 200;
  long total = 0;

  for (int i = 0; i < numCalibrationReadings; i++)
  {
    imu.readGyro();
    total += imu.g.y;
    delay(5);
  }

  gyroYOffset = (float)total / (float)numCalibrationReadings;

  Serial.print(F("Gyro Y offset measured as: "));
  Serial.println(gyroYOffset);

  const int numAccelReadings = 50;
  float accelAngleTotal = 0.0;

  for (int i = 0; i < numAccelReadings; i++)
  {
    imu.readAcc();
    accelAngleTotal += atan2((float)imu.a.x, (float)imu.a.z) * 180.0 / PI;
    delay(5);
  }

  accelAngleOffsetDegrees = accelAngleTotal / (float)numAccelReadings;

  Serial.print(F("Accelerometer angle offset measured as: "));
  Serial.println(accelAngleOffsetDegrees);

  pitchAngleDegrees = 0.0;

  lastUpdateMicros = micros();

  Serial.println(F("Tilt sensor ready."));
}



void setup(){
    Serial.begin(9600);
    Serial1.begin(9600);
    //while (!Serial);
    //delay(500);
    lineSensor.initialize();
    Serial.println("Press A to calibrate line sensors");
    //buzzer.play("T90 L8 O3 aaa f16>c16 a f16>c16 a");
    while (!buttonA.isPressed()) {
        tiltSensorSetup();
        calibrateLineSensors();
    }




    Serial.println("Calibration complete. Press B to start following the line, A to stop, and C to toggle sensor printing.");
    

    Wire.begin();
    bool foundImu = imu.init();
    if (!foundImu)
    {
    while (true)
    {
        Serial.println(F("Could not find the IMU. Check wiring."));
        delay(500);
    }
    }
    imu.enableDefault();
    tiltSensorSetup();
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

    if ((lineSensor.detectGrijs() == LineColor::GREY) && Eenkeer) {
        Serial.println("Grijs gedetecteerd");
        runCalibrationSweep();
    }
}
