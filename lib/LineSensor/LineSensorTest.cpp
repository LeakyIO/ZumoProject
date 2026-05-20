//#include <iostream>
#include <LineSensor.h>


LineSensor testL;

void setup(){
Serial.begin(115200);
testL.initialize();
  
}

void loop(){

 static uint16_t lastSampleTime = 0;

  if ((uint16_t)(millis() - lastSampleTime) >= 100)
  {
    lastSampleTime = millis();
     testL.readSensorValues();
    testL.printReadingsToSerial();
  }


}

