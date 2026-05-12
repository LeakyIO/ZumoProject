#include <Wire.h>
#include <Zumo32U4.h>
#include <Zumo32U4Motors.h>
#include <Zumo32U4Buttons.h>

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;

void setup()
{
  buttonA.waitForButton();


  delay(1000);
}



void loop()
{
  // Forward;
  ledYellow(1);
  for (int speed = 0; speed <= 400; speed++)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }
  for (int speed = 400; speed >= 0; speed--)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);

  }

  // backward.
  ledYellow(0);
  for (int speed = 0; speed >= -400; speed--)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }
  for (int speed = -400; speed <= 0; speed++)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }

  delay(500);
}
