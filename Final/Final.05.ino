#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Stepper.h>
#define TCA9548A_ADDR 0x70
Adafruit_TCS34725 sensors[4] = {
  Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X),
  Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X),
  Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X),
  Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X)
};

//Pinbelegung
int stepsToMove = 512;
const int stepsPerRevolution = 2048;
const int trigVorne = 11;
const int echoVorne = 10;
const int trigLinks = 13;
const int echoLinks = 12;
const int trigRechts = 9;
const int echoRechts = 8;
const int trigHinten = 7;
const int echoHinten = 6;
const int motor1Backward = 24;
const int motor1Forward = 26;
const int motor2Backward = 28;
const int motor2Forward = 30;
const int motor3Forward = 34;
const int motor3Backward = 32;
const int motor4Forward = 36;
const int motor4Backward = 38;
const int Enable1 = 2;
const int Enable2 = 3;
const int Enable3 = 4;
const int Enable4 = 5;
//Variabeln
int Speed = 90;
int Rechtsdrehung = 520;
int Linksdrehung = 600;


void setup() {
  Serial.begin(9600);
  pinMode(trigVorne, OUTPUT);
  pinMode(echoVorne, INPUT);
  pinMode(trigLinks, OUTPUT);
  pinMode(echoLinks, INPUT);
  pinMode(trigRechts, OUTPUT);
  pinMode(echoRechts, INPUT);
  pinMode(trigHinten, OUTPUT);
  pinMode(echoHinten, INPUT);
  pinMode(motor1Forward, OUTPUT);
  pinMode(motor1Backward, OUTPUT);
  pinMode(motor2Forward, OUTPUT);
  pinMode(motor2Backward, OUTPUT);
  pinMode(motor3Forward, OUTPUT);
  pinMode(motor3Backward, OUTPUT);
  pinMode(motor4Forward, OUTPUT);
  pinMode(motor4Backward, OUTPUT);
  pinMode(Enable1, OUTPUT);
  pinMode(Enable2, OUTPUT);
  pinMode(Enable3, OUTPUT);
  pinMode(Enable4, OUTPUT);
  for (uint8_t i = 0; i < 4; i++) {
    selectChannel(i);
    sensors[i].begin();
  }
}
void loop() {
  for (int i = 0; i < 4; i++) {
    uint16_t r = red(i);
    uint16_t g = green(i);
    uint16_t b = blue(i);

    if (b > 40 && b < 60) {
      Serial.println("Silber");
      digitalWrite(52, HIGH);
      delay(1000);
      digitalWrite(52, LOW);
    }
    if (b < 10) {
      Serial.println("Schwarz");
      digitalWrite(52, HIGH);
      delay(5000);
      digitalWrite(52, LOW);
    }
    if (b > 10 && b < 25) {
      Serial.println("Rot");
      digitalWrite(52, HIGH);
      delay(3000);
      digitalWrite(52, LOW);
    }
    Serial.begin(9600);
    Serial.println(b);
  }
  if (readUs(trigRechts, echoRechts) > 10) {
    drehenr(Rechtsdrehung);
    vorne();
    delay(710);
//  } else if (readUs(trigLinks, echoLinks) > 10) {
 //  drehenl(Linksdrehung);
 // vorne();
 //   delay(700);
  } else if (readUs(trigVorne, echoVorne) && (trigRechts, echoRechts) < 10) {
    drehenr(Rechtsdrehung * 2);
    vorne();
  }
}
void vorne() {                       // vorne
  digitalWrite(motor1Forward, LOW);  //HL
  digitalWrite(motor1Backward, HIGH);
  digitalWrite(motor2Forward, LOW);  //VL
  digitalWrite(motor2Backward, HIGH);
  digitalWrite(motor3Forward, LOW);  //VR
  digitalWrite(motor3Backward, HIGH);
  digitalWrite(motor4Forward, LOW);  //HR
  digitalWrite(motor4Backward, HIGH);
  analogWrite(Enable1, Speed);
  analogWrite(Enable2, Speed);
  analogWrite(Enable3, Speed);
  analogWrite(Enable4, Speed);
}
void stop1() {
  digitalWrite(motor1Forward, HIGH);  //HL
  digitalWrite(motor1Backward, LOW);
  digitalWrite(motor2Forward, HIGH);  //VL
  digitalWrite(motor2Backward, LOW);
  digitalWrite(motor3Forward, HIGH);  //VR
  digitalWrite(motor3Backward, LOW);
  digitalWrite(motor4Forward, HIGH);  //HR
  digitalWrite(motor4Backward, LOW);
  analogWrite(Enable1, Speed);
  analogWrite(Enable2, Speed);
  analogWrite(Enable3, Speed);
  analogWrite(Enable4, Speed);
  delay(100);
  digitalWrite(motor1Forward, LOW);
  digitalWrite(motor1Backward, LOW);
  digitalWrite(motor2Forward, LOW);
  digitalWrite(motor2Backward, LOW);
  digitalWrite(motor3Forward, LOW);
  digitalWrite(motor3Backward, LOW);
  digitalWrite(motor4Forward, LOW);
  digitalWrite(motor4Backward, LOW);
  digitalWrite(Enable1, LOW);
  digitalWrite(Enable2, LOW);
  digitalWrite(Enable3, LOW);
  digitalWrite(Enable4, LOW);
}
void stop() {
  digitalWrite(motor1Forward, LOW);
  digitalWrite(motor1Backward, LOW);
  digitalWrite(motor2Forward, LOW);
  digitalWrite(motor2Backward, LOW);
  digitalWrite(motor3Forward, LOW);
  digitalWrite(motor3Backward, LOW);
  digitalWrite(motor4Forward, LOW);
  digitalWrite(motor4Backward, LOW);
  digitalWrite(Enable1, LOW);
  digitalWrite(Enable2, LOW);
  digitalWrite(Enable3, LOW);
  digitalWrite(Enable4, LOW);
}
void drehenr(int time) {
  digitalWrite(motor1Forward, LOW);  //HL
  digitalWrite(motor1Backward, HIGH);
  digitalWrite(motor2Forward, LOW);  //VL
  digitalWrite(motor2Backward, HIGH);
  digitalWrite(motor3Forward, HIGH);  //VR
  digitalWrite(motor3Backward, LOW);
  digitalWrite(motor4Forward, HIGH);  //HR
  digitalWrite(motor4Backward, LOW);
  analogWrite(Enable1, Speed);
  analogWrite(Enable2, Speed);
  analogWrite(Enable3, Speed);
  analogWrite(Enable4, Speed);
  delay(time);
  digitalWrite(motor1Forward, LOW);
  digitalWrite(motor1Backward, LOW);
  digitalWrite(motor2Forward, LOW);
  digitalWrite(motor2Backward, LOW);
  digitalWrite(motor3Forward, LOW);
  digitalWrite(motor3Backward, LOW);
  digitalWrite(motor4Forward, LOW);
  digitalWrite(motor4Backward, LOW);
  digitalWrite(Enable1, LOW);
  digitalWrite(Enable2, LOW);
  digitalWrite(Enable3, LOW);
  digitalWrite(Enable4, LOW);
}
void drehenl(int time) {
  digitalWrite(motor1Forward, HIGH);  //HL
  digitalWrite(motor1Backward, LOW);
  digitalWrite(motor2Forward, HIGH);  //VL
  digitalWrite(motor2Backward, LOW);
  digitalWrite(motor3Forward, LOW);  //VR
  digitalWrite(motor3Backward, HIGH);
  digitalWrite(motor4Forward, LOW);  //HR
  digitalWrite(motor4Backward, HIGH);
  analogWrite(Enable1, Speed);
  analogWrite(Enable2, Speed);
  analogWrite(Enable3, Speed);
  analogWrite(Enable4, Speed);
  delay(time);
  digitalWrite(motor1Forward, LOW);
  digitalWrite(motor1Backward, LOW);
  digitalWrite(motor2Forward, LOW);
  digitalWrite(motor2Backward, LOW);
  digitalWrite(motor3Forward, LOW);
  digitalWrite(motor3Backward, LOW);
  digitalWrite(motor4Forward, LOW);
  digitalWrite(motor4Backward, LOW);
  digitalWrite(Enable1, LOW);
  digitalWrite(Enable2, LOW);
  digitalWrite(Enable3, LOW);
  digitalWrite(Enable4, LOW);
}
float readUs(int trigPin, int echoPin) {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH, 20000) * 0.034 / 2;
}
void selectChannel(uint8_t channel) {
  if (channel > 7) return;
  Wire.beginTransmission(TCA9548A_ADDR);
  Wire.write(1 << channel);
  Wire.endTransmission();
}
uint16_t red(uint8_t sensor) {
  selectChannel(sensor);
  uint16_t r, g, b, c;
  sensors[sensor].getRawData(&r, &g, &b, &c);
  return r;
}

uint16_t green(uint8_t sensor) {
  selectChannel(sensor);
  uint16_t r, g, b, c;
  sensors[sensor].getRawData(&r, &g, &b, &c);
  return g;
}

uint16_t blue(uint8_t sensor) {
  selectChannel(sensor);
  uint16_t r, g, b, c;
  sensors[sensor].getRawData(&r, &g, &b, &c);
  return b;
}
//1=Hinten 2=Vorne 3=Rechts 4=Links
