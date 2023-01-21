#include <Stepper.h>
#include <Arduino.h>

const int stepsPerRevolution = 200; // change this to match the number of steps per revolution for your stepper motor
const int ldr1Pin = A2;
const int ldr2Pin = A3;
const int maxStepCount = 500; // maximum step count limit for the stepper motor
int stepCount = 0; // current step count

Stepper motor(stepsPerRevolution,4,5); // create a stepper object

void setup() {
  motor.setSpeed(70); // set the speed of the stepper motor
}

void loop() {
  int ldr1Value = analogRead(ldr1Pin);
  int ldr2Value = analogRead(ldr2Pin);
  int ldrDiff = ldr1Value - ldr2Value;
  
  if (ldrDiff > 0 && stepCount < maxStepCount) {
    // move clockwise
    motor.step(1);
    stepCount++;
  } else if (ldrDiff < 0 && stepCount > -maxStepCount) {
    // move counter-clockwise
    motor.step(-1);
    stepCount--;
  }
  // delay is added to slow down the stepper motor and make it more visible
 // delay(50);
}
