#include "SensorsBase.h"

using namespace std;

SensorsBase::SensorsBase() : isCalibrated(false), isEnabled(true) {}

SensorsBase::~SensorsBase() {}

bool SensorsBase::initialize() {
    return true;
}

void SensorsBase::calibrate() {
    isCalibrated = true;
}

bool SensorsBase::isReady() const {
    return isEnabled && isCalibrated;
}

