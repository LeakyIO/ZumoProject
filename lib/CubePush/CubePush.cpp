#include "CubePush.h"

static const uint8_t CUBE_DETECT_THRESHOLD = 5;
static const uint8_t CUBE_CLOSE_THRESHOLD = 3;
static const uint16_t LINE_THRESHOLD = 600;

static const int CALIBRATE_SPEED = 100;
static const int SEARCH_SPEED = 200;
static const int APPROACH_SPEED = 150;
static const int PUSH_SPEED = 200;

CubePush::CubePush() : state(State::SEARCHING), frontLeftCount(0), frontRightCount(0), leftCount(0), rightCount(0), searchStartTime(0), active(false) {}


void CubePush::begin() {
    proxSensors.initThreeSensors();
    lineSensors.initThreeSensors(); 

    for (uint16_t i = 0; i < 120; i++) {
        if (i < 30 || i >= 90) {
            motors.setSpeeds(CALIBRATE_SPEED, -CALIBRATE_SPEED);
        } else {
            motors.setSpeeds(-CALIBRATE_SPEED, CALIBRATE_SPEED);
        }
        lineSensors.calibrate();
        delay(20);
    }
    motors.setSpeeds(0, 0);
    searchStartTime = 0;
    state = State::SEARCHING;
    active = true;
}

void CubePush::update() {
    if (!active) return;
    readProximity();

    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 300) {
        Serial.print("state="); Serial.print((int)state);
        Serial.print(" FL=");   Serial.print(frontLeftCount);
        Serial.print(" FR=");   Serial.println(frontRightCount);
        lastPrint = millis();
    }

    switch (state) {
        case State::LINE_FOLLOWING:
            followLine();
            break;

        case State::SEARCHING: searchForCube(); break;
        case State::APPROACHING: driveToCube(); break;
        case State::PUSHING: pushCube(); break;
        case State::FINISHED: motors.setSpeeds(0, 0); break;
    }
}

bool CubePush::isFinished() const {
    return state == State::FINISHED;
}

void CubePush::searchForCube() {
    if (searchStartTime == 0) searchStartTime = millis();

    if (atCircleEdge()) {
        searchStartTime = 0;
        state = State::LINE_FOLLOWING;
        return;
    }
    motors.setSpeeds(SEARCH_SPEED, -SEARCH_SPEED);

    if (millis() - searchStartTime >= 1000) {
        if (frontLeftCount >= CUBE_DETECT_THRESHOLD && frontRightCount >= CUBE_DETECT_THRESHOLD) {
            motors.setSpeeds(0, 0);
            searchStartTime = 0;
            state = State::APPROACHING;
        }
    }
}

void CubePush::followLine() {
    if (atCircleEdge()) {
        motors.setSpeeds(-SEARCH_SPEED, -SEARCH_SPEED);  // reverse away from boundary
    } else {
        motors.setSpeeds(0, 0);
        state = State::SEARCHING;  // clear of edge, now safe to search
    }
}

void CubePush::driveToCube() {
    motors.setSpeeds(APPROACH_SPEED, APPROACH_SPEED);
    if (cubeInFront() || atCircleEdge()) {
        motors.setSpeeds(0, 0);
        state = State::PUSHING;
    }
}

void CubePush::pushCube() {
    motors.setSpeeds(PUSH_SPEED, PUSH_SPEED);
    if (atCircleEdge()) {
        motors.setSpeeds(0, 0);
        state = State::FINISHED;
    }
}

void CubePush::readProximity() {
    proxSensors.read();
    frontLeftCount = proxSensors.countsFrontWithLeftLeds();
    frontRightCount = proxSensors.countsFrontWithRightLeds();
    leftCount = proxSensors.countsLeftWithLeftLeds();
    rightCount = proxSensors.countsRightWithRightLeds();
}

bool CubePush::cubeInFront() const {
    return frontLeftCount >= CUBE_CLOSE_THRESHOLD && 
           frontRightCount >= CUBE_CLOSE_THRESHOLD;
}

bool CubePush::atCircleEdge() {
    lineSensors.read(lineValues);

    for (uint8_t i = 0; i < 3; i++) {
        if (lineValues[i] > LINE_THRESHOLD) {
            return true;
        }
    }
    return false;
}




    






