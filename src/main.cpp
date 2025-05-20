#include <Arduino.h>
#include <Stepper.h>

volatile unsigned long timeMic1 = 0;
volatile unsigned long timeMic2 = 0;

void mic1ISR() {
  if (timeMic1 == 0) timeMic1 = micros();
}

void mic2ISR() {
  if (timeMic2 == 0) timeMic2 = micros();
}

void setup() {
  Serial.begin(9600);

  pinMode(2, INPUT); // Mic 1 digital output
  pinMode(3, INPUT); // Mic 2 digital output

  attachInterrupt(digitalPinToInterrupt(2), mic1ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(3), mic2ISR, RISING);

  Serial.println("Listening...");
}

void loop() {
  if (timeMic1 > 0 && timeMic2 > 0) {
    if (timeMic1 < timeMic2) {
      Serial.println("Mic 2 heard sound first");
    } else if (timeMic2 < timeMic1) {
      Serial.println("Mic 3 heard sound first");
    } else {
      Serial.println("Both heard at the same time");
    }

    // Reset for next detection
    timeMic1 = 0;
    timeMic2 = 0;
    delay(1000); // debounce between trials
  }
}
