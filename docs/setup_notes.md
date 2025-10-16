Software & Libraries

Install these libraries in Arduino IDE:

LiquidCrystal_I2C

RTClib (Adafruit)

DHT sensor library (Adafruit)

Adafruit Unified Sensor

SD

Wire (built-in)

3. 🧪 Uploading the Code

Connect your Arduino via USB-C.

Open sensor_logger.ino in Arduino IDE.

Verify and upload the sketch.

The LCD should display:

Time:
Date:
T:        H:

4. ⏳ Setting RTC Time

The RTC time is set automatically on upload with:

rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));


This uses your computer’s current time. You only need to do this once unless the RTC battery is removed.

5. 💾 SD Card Setup

Format your microSD card to FAT32.

Insert it into the SD card module.

After running the system, DATA.TXT will be created automatically.

Delete DATA.TXT to clear logs when needed.

6. 🧠 How It Works

RTC tracks real time.

DHT11 measures temperature and humidity.

LCD displays live values.

SD card logs data every 60 seconds.

Power flows through breadboard rails from Arduino 5V and GND.
