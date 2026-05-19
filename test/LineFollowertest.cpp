#include "MotorTest.h"
#include "LineFollowerTest.h"

MotorTest motors;
LineFollowerTest zumo;
Zumo32U4Encoders encoders;
Zumo32U4ProximitySensors prox;


void follower(){
    while (zumo.detected()) {
        if (!encoders.leftStopped() && !encoders.rightStopped() && !prox.botsing()) {
            zumo.followLine();
        }
        else {
            motors.setLeftSpeed(0);
            motors.setRightSpeed(0);
        }
    }
    
    zumo.searchLine();

}
