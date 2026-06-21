#ifndef Cube_PUSHER_H
#define Cube_PUSHER_H

#include "LineFollower.h"
#include <Zumo32U4.h>


class CubePush {
    private:
        Zumo32U4ProximitySensors proxSensors;
        Zumo32U4LineSensors lineSensors;
        MotorController motors;

        enum class State {
            LINE_FOLLOWING,
            SEARCHING,
            APPROACHING,
            PUSHING,
            FINISHED
        };

        void followLine();

        void searchForCube();
        void driveToCube();
        void pushCube();

        void readProximity();
        bool cubeInFront() const;
        bool atCircleEdge();

        State state;

        uint8_t frontLeftCount;
        uint8_t frontRightCount;
        uint8_t leftCount;
        uint8_t rightCount;
        unsigned long searchStartTime;
        bool active;

        unsigned int lineValues[3];


    

    public:
        CubePush();

        void begin();
        void update();

        bool isFinished() const;
};

#endif
        
        

        


