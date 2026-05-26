/*
 * BMP280 Pressure / Temperature / Altitude Readout
 * -------------------------------------------------
 * Reads temperature, barometric pressure, and approximate altitude from
 * a Bosch BMP280 sensor over I2C.
 *
 * Required libraries (install via Library Manager):
 *   - "Adafruit BMP280 Library" by Adafruit
 *   - "Adafruit Unified Sensor" by Adafruit  (dependency)
 *
 * Target board: Arduino Uno (or any 3.3V/5V Arduino)
 * Wiring (Adafruit BMP280 / generic GY-BMP280 breakout):
 *   BMP280 VIN  -> Arduino 5V (or 3.3V — module has onboard regulator + level shift)
 *   BMP280 GND  -> Arduino GND
 *   BMP280 SCK  -> Arduino A5 (SCL)
 *   BMP280 SDI  -> Arduino A4 (SDA)
 *
 * I2C address: 0x77 default (Adafruit board), or 0x76 (some generic clones).
 * The sketch tries 0x77 first, then falls back to 0x76.
 *
 * Open Serial Monitor at 9600 baud after upload.
 *
 * (c) 2026 Circuitrocks. Released under the MIT License.
 * https://github.com/circuitrocks
 */

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

// Local sea-level pressure in hPa. Adjust to your area for accurate altitude.
const float SEA_LEVEL_HPA = 1013.25f;

void setup() {
  Serial.begin(9600);
  while (!Serial) { /* wait for native USB boards */ }

  if (!bmp.begin(0x77) && !bmp.begin(0x76)) {
    Serial.println(F("BMP280 not found at 0x77 or 0x76. Check wiring."));
    while (1) { delay(1000); }
  }

  // Standard "weather monitoring" config from Bosch app note 2.1.
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);

  Serial.println(F("BMP280 ready."));
  Serial.println(F("temp_C\tpres_hPa\talt_m"));
}

void loop() {
  Serial.print(bmp.readTemperature(), 2);
  Serial.print('\t');
  Serial.print(bmp.readPressure() / 100.0F, 2);
  Serial.print('\t');
  Serial.println(bmp.readAltitude(SEA_LEVEL_HPA), 1);

  delay(1000);
}
