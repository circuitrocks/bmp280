# BMP280 — barometric pressure & altitude sensor

Sample sketch for the **[Adafruit BMP280 Barometric Pressure / Altitude Sensor](https://circuit.rocks/products/barometric-pressure-and-altitude-sensor-adafruit-bmp280-i2c-or-spi)**, sold by [Circuitrocks](https://circuit.rocks/).

Reads temperature, barometric pressure, and altitude over I2C using the Adafruit BMP280 library.

> **BMP280 vs BME280:** the BMP280 measures pressure + temperature. The BME280 adds humidity. If you need humidity too, use the BME280 module instead.

## What you need

- 1x Adafruit BMP280 module (or generic GY-BMP280 breakout)
- 1x Arduino Uno (or compatible)
- 4x jumper wires

## Wiring

| BMP280 pin | Arduino Uno pin |
|------------|-----------------|
| VIN        | 5V (or 3.3V)    |
| GND        | GND             |
| SCK / SCL  | A5              |
| SDI / SDA  | A4              |

The Adafruit board has an onboard 3.3 V regulator and level shifters, so 5 V on VIN is safe.

For 3.3 V boards (ESP32, Pi Pico, etc.), use that board's I2C pins. No code change needed.

## Required libraries

Install both via the Arduino IDE Library Manager (**Sketch → Include Library → Manage Libraries…**):

- **Adafruit BMP280 Library** by Adafruit
- **Adafruit Unified Sensor** by Adafruit (dependency)

## How to use

1. Open `bmp280.ino` in the Arduino IDE.
2. Select **Tools → Board → Arduino Uno** and the correct COM port.
3. Click **Upload**.
4. Open **Tools → Serial Monitor**, baud rate **9600**.
5. You'll see temperature, pressure, and altitude printed every second.

## What the values mean

- **temp_C** — temperature in °C (-40 to +85 °C, ±1 °C).
- **pres_hPa** — barometric pressure in hPa (300 – 1100 hPa, ±1 hPa).
- **alt_m** — approximate altitude in meters, calculated from pressure assuming a 1013.25 hPa sea-level reference. Set `SEA_LEVEL_HPA` in the sketch to your local value (from a weather report) for accurate altitude.

The sketch uses the **"weather monitoring"** config from Bosch's app note (oversampling x2 for temperature, x16 for pressure, IIR filter coefficient 16). Good for slow ambient measurements.

## I2C address

- **0x77** — default for the Adafruit board.
- **0x76** — some generic GY-BMP280 clones.

The sketch tries 0x77 first, then 0x76 — works with either.

## Datasheet

[BMP280 datasheet (Bosch, PDF)](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmp280-ds001.pdf)

## Troubleshooting

- **"BMP280 not found at 0x77 or 0x76"** — check wiring (especially SDA/SCL). Confirm the power LED is lit. Try an I2C scanner sketch to confirm the bus is working.
- **Pressure value drifts slowly** — that's the sensor warming up; readings stabilize after ~30 seconds.
- **Reads NaN** — usually a wiring issue. Reset the board.
- **Altitude reads wildly off** — set `SEA_LEVEL_HPA` to your local sea-level pressure. The default (1013.25) is rarely correct on a given day.

## License

MIT — see [LICENSE](LICENSE).

## Got stuck?

Drop by [circuit.rocks](https://circuit.rocks/) — happy to help our customers get their modules working.
