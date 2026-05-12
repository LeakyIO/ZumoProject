#pragma once //header guard voor beveiliging, wanneer deze header file opgeroepen wordt in andere klassen
#include <Wire.h>
#include <Zumo32U4.h>
//
Zumo32U4LineSensors LineSensor;

class LineSensor{
public:
LineSensor();
~LineSensor();

void initialize();
void calibrateLineSensors();
void printReadingsToSerial();
bool isCalibrated() const;
char getLastError() const;
int currentLinePosition() const;

private:
Zumo32U4LineSensors sensors;
unsigned int sensorValues(NUM_SENSORS);






};