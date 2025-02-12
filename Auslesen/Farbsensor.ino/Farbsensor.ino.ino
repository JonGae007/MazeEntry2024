#include <Wire.h>
#include "Adafruit_TCS34725.h"

// TCA9548A Adresse
#define TCA9548A_ADDR 0x70

// TCS34725 Sensoren
Adafruit_TCS34725 sensors[4] = {
  Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_4X),
  Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_4X),
  Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_4X),
  Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_4X)
};

void selectChannel(uint8_t channel) {
  if (channel > 7) return;
  Wire.beginTransmission(TCA9548A_ADDR);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(9600);
  Wire.begin();

  for (uint8_t i = 0; i < 4; i++) {
    selectChannel(i);
    if (sensors[i].begin()) {
      Serial.print("Sensor auf Kanal ");
      Serial.print(i);
      Serial.println(" gefunden.");
    } else {
      Serial.print("Sensor auf Kanal ");
      Serial.print(i);
      Serial.println(" nicht gefunden.");
    }
  }
}

void loop() {
  for (uint8_t i = 0; i < 4; i++) {
    selectChannel(i);
    uint16_t r, g, b, c;
    sensors[i].getRawData(&r, &g, &b, &c);
    uint16_t colorTemp = sensors[i].calculateColorTemperature(r, g, b);
    uint16_t lux = sensors[i].calculateLux(r, g, b);

    Serial.print("Kanal ");
    Serial.print(i);
    Serial.print(": R=");
    Serial.print(r);
    Serial.print(" G=");
    Serial.print(g);
    Serial.print(" B=");
    Serial.print(b);
    Serial.print(" C=");
    Serial.print(c);
    Serial.print(" Farbtemperatur=");
    Serial.print(colorTemp);
    Serial.print("K Lux=");
    Serial.println(lux);
  }
  delay(1000);
}