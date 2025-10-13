# arduino-temp-and-humidity-sensor
A real time temperature and humidity monitoring project using Arduino Uno R4 Minima, RTC DS3231, DHT11 sensor, and 20x4 I2C LCD

---

# 🌡️ Arduino Sensor Logger

A real-time environmental monitoring project using **Arduino UNO R4**, a **DHT11 temperature & humidity sensor**, a **DS1307 RTC module**, and a **20x4 I2C LCD display**. The system displays live temperature, humidity, and time, and can optionally log data to an SD card.

---

## 🧠 Features
- ⏰ Real-time clock using DS1307 RTC
- 🌡️ Live temperature and humidity display with DHT11
- 🖥️ 20x4 I2C LCD display
- 💾 Optional SD card logging
- 🔌 Powered by Arduino 5 V

---

## 🧰 Components Used
- Arduino UNO R4 Minima
- DHT11 Sensor
- DS1307 RTC Module
- 20x4 I2C LCD
- Breadboard + jumper wires
- MicroSD card module (optional)
- MicroSD card
- USB-C cable for power and upload

---

## 🪛 Key Connectiona

| Component | VCC | GND | SDA | SCL | DATA |
|-----------|-----|-----|-----|-----|------|
| RTC       | + rail (5 V) | - rail (GND) | SDA | SCL | — |
| LCD       | + rail (5 V) | - rail (GND) | SDA | SCL | — |
| DHT11     | + rail (5 V) | - rail (GND) | — | — | D8 |

👉 SDA and SCL are shared between multiple devices on the same breadboard row.

---

## 🧾 How It Works
- Arduino powers the + and – rails on the breadboard.  
- All modules pull power from those rails.  
- SDA/SCL lines are tied together in a single breadboard row.  
- DHT11 outputs temperature and humidity to Arduino through digital pin 8.  
- RTC keeps track of real time.
- LCD displays the data in real time.

---
