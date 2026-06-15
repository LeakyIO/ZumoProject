#include "LineFollower.h"

const uint16_t maxSpeed = 180;

// uint16_t minSpeed = 80;

LineFollower::LineFollower(MotorController& motors, LineSensor& sensor)
    : motors(motors), sensor(sensor) {}
 unsigned int minGroenValue = 50;
    unsigned int maxGroenValue = 150;
    unsigned int minGrijsValue = 300;
    unsigned int maxGrijsValue = 450;
    unsigned int wit = 30;
    unsigned int zwartMax = 1000;
    unsigned int zwartMin = 800; 
   
    

void LineFollower::follow() {


//kruispunt detectie
    bool bijkruispunt = sensor.sensorValues[0] > zwartMin && sensor.sensorValues[4] > zwartMin;
 if (bijkruispunt) {
    if (draaiRechts) {
    doeRechtsAfslag();
    draaiRechts = false;   
        } 

else {
      rechtdoorOverKruising();
        }
        return;   
    }


//moment naar rechts draaien
    unsigned int rechts = max(sensor.sensorValues[3], sensor.sensorValues[4]);
    if (rechts > minGrijsValue && rechts < maxGrijsValue) {
        draaiRechts = true;
        Serial.println("grijs gezien, draai rechts bij kruising");
    }


    //PID werking, lasterror = error, terugkoppeling, kp en kd gebruikt dus PD in feite.
    const unsigned int Kp = 2;
    const unsigned int Kd = 6;

    int16_t position = sensor.readLine();
    int16_t error = position - 2000;
    int16_t speedDifference = error / Kp + Kd * (error - lastError);
    lastError = error;


//set speed forceren tussen 0 en max speed met de speeddifference corrigering (PID werking)
    int16_t baseLeftSpeed = constrain((int16_t)maxSpeed + speedDifference, 0, (int16_t)maxSpeed);
    int16_t baseRightSpeed = constrain((int16_t)maxSpeed - speedDifference, 0, (int16_t)maxSpeed);
    int16_t leftSpeed;
    int16_t rightSpeed;
    // motors.setSpeeds(leftSpeed, rightSpeed);

    
    //waarde ophalen van sensoren
      unsigned int maxWaarde = sensor.getMaxSensorValue();

    if(maxWaarde <=  wit){ 

         Serial.println("wit");
        leftSpeed = baseLeftSpeed/2;
        rightSpeed = baseRightSpeed/2;
    } 
    else if(maxWaarde > minGroenValue && maxWaarde <maxGroenValue){

        Serial.println("Groen");
        leftSpeed = baseLeftSpeed/2;
        rightSpeed = baseRightSpeed/2;
        // motors.setSpeeds(0, 0);
        // leftSpeed = 0;
        // rightSpeed = 0;
    }
    else if(sensor.sensorValues[ 4] > minGrijsValue && sensor.sensorValues[4]<maxGrijsValue){
        Serial.println("grijs");
        leftSpeed = baseLeftSpeed/4;
        rightSpeed = baseRightSpeed/4;
        //turn right at next crossing function how
    }
    else {
        leftSpeed = baseLeftSpeed;
        rightSpeed = baseRightSpeed;
        Serial.println("hoogstwaarschijnlijk zwart of van de tafel afgevallen");
    }

    // static unsigned long lastPrint = 0;
    // if (millis() - lastPrint >= 1000) {
    //     Serial.println(String(leftSpeed) + ',' + rightSpeed + '|' + color);
    // }


    motors.setSpeeds(leftSpeed, rightSpeed);
}

void  LineFollower::rechtdoorOverKruising() {
    motors.setSpeeds(maxSpeed, maxSpeed);
    delay(150);   
}

void LineFollower::doeRechtsAfslag() {
    // 1. Iets vooruit zodat wielen op de kruising staan
    motors.setSpeeds(200, 200);
    delay(150);
    
    // 2. Draai rechts tot middelste sensor weer zwart ziet
    motors.setSpeeds(200, -200);
    delay(200);   // blind beginnen, anders detecteert hij meteen huidige lijn
    while (sensor.sensorValues[2] < zwartMin) {
        sensor.readLine();
        motors.setSpeeds(200, -200);
    }
    motors.stop();
}