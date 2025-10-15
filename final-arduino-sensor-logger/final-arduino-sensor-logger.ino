#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <DHT.h>

#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 20, 4);
RTC_DS3231 rtc;

#define SD_CS_PIN 10
const char* LOG_FILENAME = "DATA.TXT";

const unsigned long LOG_INTERVAL = 60000UL;
unsigned long lastLogTime = 0UL;

#define BUTTON_PIN 2

const unsigned long BACKLIGHT_DURATION = 60000UL;

bool backlightActive = false;
unsigned long backlightTurnOnMillis = 0;

bool lastButtonState = HIGH;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  lcd.init();

  lcd.backlight();


  dht.begin();

  if(!rtc.begin()) {
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("RTC not found!");
    while(true) { /* Halt */ }
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));


  pinMode(SD_CS_PIN, OUTPUT);
  if(!SD.begin(SD_CS_PIN)) {
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SD init failed!");
    while (true) { /* Halt if no SD */ }
  }
  

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lastButtonState = digitalRead(BUTTON_PIN);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Time:");

  lcd.setCursor(0, 1);
  lcd.print("Date:");

  lcd.setCursor(0, 3);
  lcd.print("T:");
  lcd.setCursor(10, 3);
  lcd.print("H:");  
}

void loop() {
  // put your main code here, to run repeatedly:

  // --- Button removed for testing ---
  // bool currentButtonState = digitalRead(BUTTON_PIN);
  // if(lastButtonState == HIGH && currentButtonState == LOW) {
  //   lcd.backlight();
  //   backlightActive = true;
  //   backlightTurnOnMillis = millis();
  // }
  // lastButtonState = currentButtonState;
  // if (backlightActive && (millis() - backlightTurnOnMillis >= BACKLIGHT_DURATION)) {
  //   lcd.noBacklight();
  //   backlightActive = false;
  // }


  DateTime now = rtc.now();

  int hour24 = now.hour();
  int displayHour = hour24;
  bool isPM = false;
  if (displayHour >= 12) {
    isPM = true;
  }
  if (displayHour == 0) {
    displayHour = 12;
  } else if (displayHour > 12) {
    displayHour -= 12;
  }

  char timeString[10];
  snprintf(timeString, sizeof(timeString), "%02d:%02d:%02d",
  displayHour, now.minute(), now.second());

  lcd.setCursor(6, 0);
  lcd.print(timeString);
  lcd.print(" ");
  lcd.print(isPM ? "PM" : "AM");

  lcd.setCursor(6, 1);
  lcd.print(now.year());
  lcd.print("-");
  lcd.print(now.month());
  lcd.print("-");
  lcd.print(now.day());

  float humidity = dht.readHumidity();
  float temperatureF = dht.readTemperature(true);

  if (isnan(humidity) || isnan(temperatureF)) { 
    lcd.setCursor(3, 3);
    lcd.print("Error ");
    lcd.setCursor(13, 3);
    lcd.print(" ");
  } else {
    lcd.setCursor(3, 3);
    lcd.print(temperatureF, 1);
    lcd.print((char)223);
    lcd.print("F ");
    lcd.setCursor(13, 3);
    lcd.print(humidity, 0);
    lcd.print("% ");
  }

  unsigned long currentMillis = millis();
  if (currentMillis - lastLogTime >= LOG_INTERVAL) {
    lastLogTime = currentMillis;

    File dataFile = SD.open(LOG_FILENAME, FILE_WRITE);
    if (dataFile) {
      dataFile.print(now.year());
      dataFile.print("-");
      dataFile.print(now.month());
      dataFile.print("-");
      dataFile.print(now.day());
      dataFile.print(" ");

      char logTimeString[10];
      snprintf(logTimeString, sizeof(logTimeString), "%02d:%02d:%02d", displayHour, now.minute(), now.second());
      dataFile.print(logTimeString);
      dataFile.print(isPM ? " PM" : " AM");
      dataFile.print(",");

      if (!isnan(temperatureF)) {
        dataFile.print(temperatureF, 1);
      } else {
        dataFile.print("NaN");
      }
      dataFile.print(",");

      if(!isnan(humidity)) {
        dataFile.print(humidity, 0);
      } else {
        dataFile.print("NaN");
      }

      dataFile.println();
      dataFile.close();
    } 
  }

  Serial.print("Logging: ");
  Serial.print("Time: ");
  Serial.print(now.year());
  Serial.print("-");
  Serial.print(now.month());
  Serial.print("-");
  Serial.print(now.day());
  Serial.print(" ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.print(now.second());

  Serial.print("   Temp: ");
  Serial.print(temperatureF);
  Serial.print("F");

  Serial.print("   Humidity: ");
  Serial.print(humidity);
  Serial.println("%"); 

  delay(200);
}
