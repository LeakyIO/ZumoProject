/**
 * @file LineSensor.h
 * @brief Header file voor de LineSensor klasse van de Zumo32U4 robot
 * @author Kandhai Aditya (25103334)
 * @date 13/5/2026
 * @version 1.0
 */

#pragma once

#include <Wire.h>
#include <Zumo32U4.h>

/// Aantal lijn sensoren op de Zumo32U4
#define NUM_SENSORS 5

/**
 * @class LineSensor
 * @brief Klasse voor het aansturen en uitlezen van de lijn sensoren
 * 
 * Deze klasse biedt functionaliteit voor het initialiseren, kalibreren
 * en uitlezen van de vijf lijn sensoren op de Zumo32U4 robot.
 */
class LineSensor {
public:
    /**
     * @brief Constructor van de LineSensor klasse
     */
    LineSensor();
    
    /**
     * @brief Destructor van de LineSensor klasse
     */
    ~LineSensor();

    /**
     * @brief Kalibreert de lijn sensoren
     * 
     * Kalibreert de sensoren door minimale en maximale waarden te bepalen.
     * De robot moet tijdens kalibratie over de lijn bewogen worden.
     */
    void calibrateLineSensors();
    
    /**
     * @brief Initialiseert de lijn sensoren
     * @param calibrate Indien true, worden de sensoren direct gekalibreerd (standaard: true)
     */
    void initialize(bool calibrate = true);
    
    /**
     * @brief Print de sensor waarden naar de serial monitor
     * 
     * Gebruikt voor debugging en monitoring van sensor data
     */
    void printReadingsToSerial();
    
    /**
     * @brief Leest de huidige sensor waarden in
     * 
     * Slaat de gelezen waarden op in het private sensorValues array
     */
    void readSensorValues();
    
    /**
     * @brief Geeft aan of de sensoren gekalibreerd zijn
     */
    bool isCalibrated;

private:
    /// Zumo32U4 lijn sensor object
    Zumo32U4LineSensors sensors;
    
    /// Array voor het opslaan van sensor waarden
    unsigned int sensorValues[NUM_SENSORS];
};