#include <Arduino.h>
#include <Stepper.h>

int pin = 7;
int pin2 = 8;

unsigned long lastMic1 = 0;
unsigned long lastMic2 = 0;

void setup() {
  pinMode(pin, INPUT);
  pinMode(pin2, INPUT);
  Serial.begin(9600);   
}

void loop() {
  bool mic1 = digitalRead(pin) == HIGH;
  bool mic2 = digitalRead(pin2) == HIGH;

  unsigned long now = micros();

  if (mic1 && lastMic1 == 0) {
    lastMic1 = now;
  }
  if (mic2 && lastMic2 == 0) {
    lastMic2 = now;
  }

  // When both have detected, compare times
  if (lastMic1 > 0 && lastMic2 > 0) {
    if (lastMic1 < lastMic2) {
      Serial.print("Mic 1 (Pin 7) detected first at ");
      Serial.print(lastMic1);
      Serial.println(" ms");
    } else if (lastMic2 < lastMic1) {
      Serial.print("Mic 2 (Pin 8) detected first at ");
      Serial.print(lastMic2);
      Serial.println(" ms");
    } else {
      Serial.print("Both mics detected at the same time: ");
      Serial.print(lastMic1);
      Serial.println(" ms");
    }
    // Reset for next detection
    lastMic1 = 0;
    lastMic2 = 0;
    delay(500); // Debounce
  }

  // Reset if neither is HIGH
  if (!mic1) lastMic1 = 0;
  if (!mic2) lastMic2 = 0;
}