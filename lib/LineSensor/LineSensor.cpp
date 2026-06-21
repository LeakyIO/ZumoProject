#include "LineSensor.h"

void LineSensor::calibrate() {
    sensors.calibrate();
}

void LineSensor::initialize() {
    sensors.initFiveSensors();
}

int16_t LineSensor::readLine() {
    sensors.readCalibrated(sensorValues);
    uint32_t sum = 0;
    uint32_t weighted = 0;
    for (uint8_t i = 0; i < NUM_SENSORS; i++) {
        if (sensorValues[i] > THRESHOLD_LINE) {
            weighted += (uint32_t)sensorValues[i] * (i * 1000);
            sum += sensorValues[i];
        }
    }
    if (sum == 0) return 2000;
    return weighted / sum;
}

uint16_t LineSensor::getLeftReflectance() {
    return (sensorValues[0] + sensorValues[1]) / 2;
}

uint16_t LineSensor::getMiddleReflectance() {
    return sensorValues[2];
}

uint16_t LineSensor::getRightReflectance() {
    return (sensorValues[3] + sensorValues[4]) / 2;
}

uint16_t LineSensor::getLineReflectance() {
    uint32_t sum = 0;
    uint8_t count = 0;
    for (uint8_t i = 0; i < NUM_SENSORS; i++) {
        if (sensorValues[i] > THRESHOLD_LINE) {
            sum += sensorValues[i];
            count++;
        }
    }
    return count > 0 ? sum / count : 0;
}

LineColor LineSensor::colorFromReflectance(uint16_t r) {
    if (r == 0)               return LineColor::UNKNOWN;
    if (r < THRESHOLD_GREEN)  return LineColor::GREEN;
    if (r < THRESHOLD_GREY)   return LineColor::GREY;
    if (r < THRESHOLD_BROWN)  return LineColor::BROWN;
    return LineColor::UNKNOWN;
}

LineColor LineSensor::debouncedColor(uint16_t r) {
    LineColor raw = colorFromReflectance(r);
    if (raw == _pendingColor) {
        if (++_pendingCount >= COLOR_DEBOUNCE)
            _confirmedColor = _pendingColor;
    } else {
        _pendingColor = raw;
        _pendingCount = 1;
    }
    return _confirmedColor;
}

LineColor LineSensor::detectColor() {
    return debouncedColor(getLineReflectance());
}

LineColor LineSensor::detectLeftColor() {
    return debouncedColor(getLeftReflectance());
}


LineColor LineSensor::detectRightColor() {
    return debouncedColor(getRightReflectance());
}


LineColor LineSensor::detectGrijs()
{
  uint16_t left = getLeftReflectance();
  uint16_t right = getRightReflectance();

  bool leftIsGrey = (left >= 500 && left <= 750);
  bool rightIsGrey = (right >= 500 && right <= 750);

  if (leftIsGrey && rightIsGrey)
  {
    return LineColor::GREY;
  }

  return LineColor::UNKNOWN;
}