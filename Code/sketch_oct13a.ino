#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pin configuration
const int moisturePin = A0;
const int relayPin = 7;

// Calibration values
const int DRY_VALUE = 950;
const int WET_VALUE = 250;
const int WATERING_THRESHOLD = 600;

// Relay is active LOW
const int PUMP_ON = LOW;
const int PUMP_OFF = HIGH;

void setup() {
  Serial.begin(9600);

  digitalWrite(relayPin, PUMP_OFF);
  pinMode(relayPin, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed!");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("SAND MOISTURE");
  display.println("SYSTEM STARTING...");
  display.display();

  delay(1500);
}

void loop() {
  int sensorValue = analogRead(moisturePin);

  // Convert sensor reading to approximate moisture percentage
  int moisturePercent = map(
    sensorValue,
    DRY_VALUE,
    WET_VALUE,
    0,
    100
  );

  moisturePercent = constrain(moisturePercent, 0, 100);

  bool isDry = sensorValue >= WATERING_THRESHOLD;

  // Control pump
  digitalWrite(relayPin, isDry ? PUMP_ON : PUMP_OFF);

  // Update OLED
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("SAND MOISTURE SYSTEM");

  display.drawLine(0, 12, 127, 12, SSD1306_WHITE);

  display.setCursor(0, 19);
  display.print("Sensor: ");
  display.println(sensorValue);

  display.setCursor(0, 31);
  display.print("Moisture: ");
  display.print(moisturePercent);
  display.println("%");

  display.setCursor(0, 43);
  display.print("Status: ");
  display.println(isDry ? "DRY" : "MOIST");

  display.setCursor(0, 55);
  display.print("Pump: ");
  display.println(isDry ? "ON" : "OFF");

  display.display();

  // Serial Monitor
  Serial.print("Sensor: ");
  Serial.print(sensorValue);
  Serial.print(" | Moisture: ");
  Serial.print(moisturePercent);
  Serial.print("% | Pump: ");
  Serial.println(isDry ? "ON" : "OFF");

  delay(1000);
}