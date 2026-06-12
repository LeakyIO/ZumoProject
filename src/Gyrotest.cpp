/* Zumo32U4 Gyroscoop - Y en Z as meting
 * Gecorrigeerde versie
 */ 
#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4IMU imu;

float offsetY = 0;
float offsetZ = 0;
float hoekY = 0;
float hoekZ = 0;
unsigned long vorigeTijd = 0;
long somY = 0;
long somZ = 0;


// ─────────────────────────────────────────
// KALIBRATIE
// ─────────────────────────────────────────
void calibrateGyro() {
  Serial.println("Kalibreren... houd robot stil.");

  int samples = 1000;
  
  

  for (int i = 0; i < samples; i++) {
    imu.read();
    somY += imu.g.y;
    somZ += imu.g.z;  // Beide assen tegelijk meten
    delay(5);
  }

  offsetY = (float)somY / samples;
  offsetZ = (float)somZ / samples;

  Serial.print("Offset Y: "); Serial.println(offsetY);
  Serial.print("Offset Z: "); Serial.println(offsetZ);
  Serial.println("Kalibratie klaar");
}

// ─────────────────────────────────────────
// SETUP
// ─────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!imu.init()) {
    ledRed(1);
    while (1) {
      Serial.println("IMU init mislukt.");
      delay(1000);
    }
  }

  imu.enableDefault();
  calibrateGyro();
  vorigeTijd = millis();
}

// ─────────────────────────────────────────
// LOOP
// ─────────────────────────────────────────
void loop() {
  imu.read();

  unsigned long nu = millis();
  float dt = (nu - vorigeTijd) / 1000.0;  // ms naar seconden
  vorigeTijd = nu;

  // Gecalibreerde raw waarden
  float rawY = imu.g.y - offsetY;
  float rawZ = imu.g.z - offsetZ;

  // Driftdrempel (kleine waarden negeren)
  if (abs(rawY) < 3) rawY = 0;
  if (abs(rawZ) < 3) rawZ = 0;

  // Omrekenen naar dps en integreren
  float dpsy = rawY * 8.75 / 1000.0;
  float dpsz = rawZ * 8.75 / 1000.0;

  hoekY += dpsy * dt;
  hoekZ += dpsz * dt;

  // Printen
    somY = imu.g.y; //ruwe waardes
    somZ = imu.g.z; 
  Serial.print("Hoek Y: "); Serial.print(hoekY, 1); Serial.print(" graden"); Serial.print(" | gemiddelde offset: "); Serial.print(offsetY); Serial.print(" | offset: "); Serial.print(somY); Serial.print(" | Raw: "); Serial.println(rawY); 
  Serial.print("Hoek Z: "); Serial.print(hoekZ, 1); Serial.print(" graden"); Serial.print(" | gemiddelde offset: "); Serial.print(offsetZ); Serial.print(" | offset: "); Serial.print(somZ); Serial.print(" | Raw: "); Serial.println(rawZ); 
  Serial.println("---");

  delay(50);
}