#include <Wire.h>
#include <Zumo32U4.h>
#include <LineSensor.h>



LineSensor::LineSensor(): isCalibrated(false){

}

LineSensor::~LineSensor(){

}

void LineSensor::initialize(bool calibrate) {
 sensors.initFiveSensors();

    if(calibrate == true){
        sensors.calibrate();
        isCalibrated = true;
    }
}

void LineSensor::readSensorValues(){
    if(isCalibrated){
        sensors.readCalibrated(sensorValues);
    }
    else{
         sensors.read(sensorValues);
    }
}


void LineSensor::printReadingsToSerial(){
  char buffer[80];
  sprintf(buffer, "%4d %4d %4d %4d %4d\n",
    sensorValues[0],
    sensorValues[1],
    sensorValues[2],
    sensorValues[3],
    sensorValues[4]
  );
  Serial.print(buffer);



}