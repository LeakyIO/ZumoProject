#pragma once
#include <MotorController.h>
#include <LineSensor.h>

/**
 * @brief Implementeert PID-gebaseerde lijnvolging voor de Zumo32U4.
 *
 * De klasse combineert sensordata van LineSensor met motorsturing via
 * MotorController. Elke aanroep van follow() voert één regelcyclus uit:
 * lijnpositie bepalen, PID-correctie berekenen en motorsnelheden instellen.
 *
 * De PID-regeling werkt als volgt:
 * - De proportionele term (Kp = 0.5) stuurt op de huidige afwijking van het midden (positie 2000).
 * - De differentiële term (Kd = 7) stuurt op de verandering van de fout ten opzichte van de vorige cyclus.
 * - De basissnelheid wordt verlaagd naarmate de fout groter is, zodat de robot trager rijdt in bochten.
 */
class LineFollower {
public:

    LineFollower(MotorController& motors, LineSensor& sensor);

    /**
     * @brief Voert één lijnvolgcyclus uit.
     *
     * Leest de lijnpositie via LineSensor::readLine() en past de motorsnelheden
     * aan op basis van een PID-regeling. De volgende situaties worden afgehandeld:
     * - *Geen lijn gedetecteerd* (getLineReflectance() == 0): de robot rijdt
     *   rechtdoor of draait op halve snelheid op basis van de laatste bekende fout (lastError),
     *   totdat de lijn opnieuw gevonden wordt.
     * - *Lijn niet centraal* (getMiddleReflectance() < THRESHOLD_LINE): de robot
     *   draait naar links of rechts op basis van welke zijsensor de lijn nog ziet,
     *   totdat de middelste sensor de lijn terugvindt.
     * - *Normale lijnvolging*: PID-correctie berekent een snelheidsverschil tussen
     *   linker en rechter motor. De basissnelheid wordt verlaagd bij grotere fout.
     *   Op groene lijnsegmenten wordt de maximumsnelheid gehalveerd via greenSpeed().
     */
    void follow();

private:

    /** @brief Referentie naar de MotorController voor het instellen van motorsnelheden. */
    MotorController& motors;

    /** @brief Referentie naar de LineSensor voor lijnpositie en kleurdetectie. */
    LineSensor& sensor;

    /**
     * @brief Fout van de vorige regelcyclus, gebruikt voor de differentiële PID-term.
     *
     * Wordt bijgewerkt aan het einde van elke follow()-aanroep. Bij verlies van
     * de lijn bepaalt de tekenwaarde van lastError de draairichting van de robot.
     */
    int16_t lastError = 0;

    /**
     * @brief Maximale motorsnelheid onder normale omstandigheden.
     *
     * Wordt gehalveerd op groene lijnsegmenten via greenSpeed().
     * Eenheid: motorstappen (−400 tot 400 voor de Zumo32U4).
     */
    int16_t maxSpeed = 300;

    /**
     * @brief Geeft de maximumsnelheid terug op basis van de gedetecteerde lijnkleur.
     *
     * Controleert of de linker-, rechter- of middelste sensor een groene lijn
     * detecteert via LineSensor::detectLeftColor(), detectRightColor() en detectColor().
     * Op groene segmenten wordt maxSpeed gehalveerd om nauwkeurigere sturing
     * bij richtingsindicatoren mogelijk te maken.
     *
     * @return maxSpeed / 2 als een groene lijn gedetecteerd wordt, anders maxSpeed.
     */
    int16_t greenSpeed();
};