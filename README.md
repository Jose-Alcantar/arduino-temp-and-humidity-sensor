# arduino-temp-and-humidity-sensor
A real time temperature and humidity monitoring project using Arduino Uno R4 Minima, RTC DS3231, DHT11 sensor, and 20x4 I2C LCD

---

# Arduino Sensor Logger

A real-time environmental monitoring project using Arduino UNO R4 Minima, a DHT11 temperature & humidity sensor, a DS3231 RTC module, and a 20x4 I2C LCD display. The system displays live temperature, humidity, and time, and logs data to an SD card.

---

## Features
- Real-time clock using DS1307 RTC
- Live temperature and humidity display with DHT11
- 20x4 I2C LCD display
- SD card logging
- Powered by Arduino 5 V

---

## Components Used
- Arduino UNO R4 Minima
- DHT11 Sensor
- DS1307 RTC Module
- 20x4 I2C LCD
- Breadboard + jumper wires
- MicroSD card module (optional)
- MicroSD card
- USB-C cable for power and upload

---

## Key Connections

| Component | VCC | GND | SDA | SCL | DATA | CS | MOSI | MISO | SCK |
|-----------|-----|-----|-----|-----|------|----|------|------|-----|
| RTC       | + rail (5 V) | - rail (GND) | SDA | SCL | — | — | — | — | — |
| LCD       | + rail (5 V) | - rail (GND) | SDA | SCL | — | — | — | — | — |
| DHT11     | + rail (5 V) | - rail (GND) | — | — | D8 | — | — | — | — |
| SD card module | + rail (5 V) | - rail (GND) | — | — | — | D10 | D11 | D12 | D13 |

SDA and SCL are shared between multiple devices on the same breadboard row.

---

## How It Works
- Arduino powers the + and – rails on the breadboard.  
- All modules pull power from those rails.  
- SDA/SCL lines are tied together in a single breadboard row.  
- DHT11 outputs temperature and humidity to Arduino through digital pin 8.  
- RTC keeps track of real time.
- The Arduino communicates with the SD card module over SPI (pins D10–D13). Every logging interval the Arduino writes the current timestamp, temperature, and humidity to a file on the SD card.
- LCD displays the data in real time.

---
