
#pragma once
#include <Zumo32U4.h>

/** @brief Aantal reflectiesensoren op de Zumo32U4. */
#define NUM_SENSORS 5

/**
 * @defgroup Thresholds Kleurdrempelwaarden
 * @brief Gekalibreerde drempelwaarden voor kleurherkenning via getLineReflectance().
 *

/** @brief Maximale reflectiewaarde die als groen wordt geclassificeerd. */
#define THRESHOLD_GREEN 280

/** @brief Maximale reflectiewaarde die als bruin wordt geclassificeerd. */
#define THRESHOLD_BROWN 430

/** @brief Maximale reflectiewaarde die als grijs wordt geclassificeerd. */
#define THRESHOLD_GREY 730

/**
 * @brief Minimale reflectiewaarde om een sensor als actief (op lijn) te beschouwen.
 *
 * Waarden onder deze drempel worden gezien als sensorruis
 */
#define THRESHOLD_LINE 30

/**
 * @brief Aantal opeenvolgende gelijke lezingen vereist voordat een kleur wordt bevestigd.
 *
 * Voorkomt valse kleurdetecties door korte ruis of reflectievariaties.
 */
#define COLOR_DEBOUNCE 7

/**
 * @brief Gedetecteerde lijnkleur.
 *
 * Wordt gebruikt door detectColor(), detectLeftColor() en detectRightColor()
 * om de kleur van de lijn onder de sensor aan te geven.
 */
enum class LineColor
{
    UNKNOWN, ///< Kleur onbekend of geen lijn gedetecteerd.
    GREEN,   ///< Groene lijn gedetecteerd.
    GREY,    ///< Grijze lijn gedetecteerd.
    BROWN    ///< Bruine lijn gedetecteerd.
};

class LineSensor
{
public:
    /**
     * @brief Initialiseert de vijf reflectiesensoren.
     *
     * Configureert de Zumo32U4LineSensors voor gebruik met alle vijf sensoren.
     * Moet aangeroepen worden vóór calibrate() en alle andere methoden.
     */
    void initialize();

    /**
     * @brief Kalibreert de sensoren op de huidige omgeving.
     *
     * Legt de minimum- en maximumwaarden vast door de sensor over zowel de
     * lijn (donkerste waarde) als de witte ondergrond (lichtste waarde) te bewegen.
     * Na kalibratie geven de sensorwaarden genormaliseerde waarden (0–1000) terug.
     */
    void calibrate();

    /**
     * @brief Berekent de positie van de lijn ten opzichte van de robot.
     *
     * Leest de gekalibreerde sensorwaarden uit en berekent een gewogen gemiddelde
     * op basis van de sensoren die boven THRESHOLD_LINE uitkomen. De gewichten zijn
     * gebaseerd op de sensorindex vermenigvuldigd met 1000.
     *
     * @return Lijnpositie als waarde tussen 0 (uiterst links) en 4000 (uiterst rechts).
     *         Geeft 2000 terug als geen enkele sensor boven de drempel zit (geen lijn
     *         gedetecteerd), zodat de robot naar het midden corrigeert.
     */
    int16_t readLine();

    /**
     * @brief Detecteert de kleur van de lijn onder het midden van de robot.
     *
     * Gebruikt het gemiddelde van alle sensoren die boven THRESHOLD_LINE zitten
     * en past debouncing toe om stabiele kleurherkenning te garanderen.
     *
     * @return De gedetecteerde LineColor. Geeft LineColor::UNKNOWN terug als
     *         geen lijn wordt gevonden of de kleur niet wordt herkend.
     *
     * @see detectLeftColor(), detectRightColor()
     */
    LineColor detectColor();

    /**
     * @brief Detecteert de kleur van de lijn onder de linkerzijde van de robot.
     *
     * Gebruikt het gemiddelde van de twee meest linkse sensoren (index 0 en 1)
     * en past debouncing toe.
     *
     * @return De gedetecteerde LineColor aan de linkerzijde.
     *
     * @see detectColor(), detectRightColor()
     */
    LineColor detectLeftColor();

    /**
     * @brief Detecteert de kleur van de lijn onder de rechterzijde van de robot.
     *
     * Gebruikt het gemiddelde van de twee meest rechtse sensoren (index 3 en 4)
     * en past debouncing toe.
     *
     * @return De gedetecteerde LineColor aan de rechterzijde.
     *
     * @see detectColor(), detectLeftColor()
     */
    LineColor detectRightColor();

    /**
     * @brief Geeft de gemiddelde reflectiewaarde van alle actieve sensoren.
     *
     * Berekent het gemiddelde van alle sensorwaarden die boven THRESHOLD_LINE
     * uitkomen. Wordt gebruikt als invoer voor kleurclassificatie.
     *
     * @return Gemiddelde reflectiewaarde (0–1000). Geeft 0 terug als geen
     *         sensor boven de drempel zit.
     */
    uint16_t getLineReflectance();

    /**
     * @brief Geeft de gemiddelde reflectiewaarde van de linkerzijde.
     *
     * Berekent het gemiddelde van sensor 0 (uiterst links) en sensor 1.
     *
     * @return Gemiddelde reflectiewaarde van de twee linkse sensoren (0–1000).
     */
    uint16_t getLeftReflectance();

    /**
     * @brief Geeft de reflectiewaarde van de middelste sensor.
     *
     * Leest sensor 2 (het midden van de vijf sensoren) direct uit.
     * Wordt gebruikt in LineFollower om te detecteren of de lijn
     * nog centraal onder de robot zit.
     *
     * @return Reflectiewaarde van sensor 2 (0–1000).
     */
    uint16_t getMiddleReflectance();

    /**
     * @brief Geeft de gemiddelde reflectiewaarde van de rechterzijde.
     *
     * Berekent het gemiddelde van sensor 3 en sensor 4 (uiterst rechts).
     *
     * @return Gemiddelde reflectiewaarde van de twee rechtse sensoren (0–1000).
     */
    uint16_t getRightReflectance();

    /**
     * @brief Gebruikt left en right reflectance om te zien of beide grijs returnen
     *
     * @return de gedetecteerde LineColor aan de uiterst linker en rechterzijde.
     */
    LineColor detectGrijs();

private:
    /** @brief Interne Zumo32U4-bibliotheekinstantie voor hardware-aansturing. */
    Zumo32U4LineSensors sensors;

    /** @brief Array met de meest recent uitgelezen gekalibreerde sensorwaarden (0–1000). */
    unsigned int sensorValues[NUM_SENSORS];

    /**
     * @brief Classificeert een reflectiewaarde naar een LineColor.
     *
     * Vergelijkt de gegeven waarde met de gedefinieerde drempelwaarden
     * (THRESHOLD_GREEN, THRESHOLD_GREY, THRESHOLD_BROWN) en geeft de
     * bijbehorende kleur terug.
     *
     * @param r Reflectiewaarde om te classificeren (0–1000).
     * @return De geclassificeerde LineColor.
     */
    LineColor colorFromReflectance(uint16_t r);

    /**
     * @brief Past debouncing toe op een ruwe kleurclassificatie.
     *
     * Bevestigt een kleurverandering pas nadat COLOR_DEBOUNCE opeenvolgende
     * lezingen dezelfde kleur tonen. Voorkomt valse detecties door
     * kortstondige reflectievariaties.
     *
     * @param r Reflectiewaarde van de huidige cyclus.
     * @return De bevestigde LineColor na debouncing.
     */
    LineColor debouncedColor(uint16_t r);

    /** @brief Kleur die momenteel in afwachting is van bevestiging. */
    LineColor _pendingColor = LineColor::UNKNOWN;

    /** @brief Laatste bevestigde kleur na debouncing. */
    LineColor _confirmedColor = LineColor::UNKNOWN;

    /** @brief Aantal opeenvolgende lezingen van _pendingColor. */
    uint8_t _pendingCount = 0;
};