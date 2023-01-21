#include <Stepper.h>
#include <Arduino.h>

const int stepsPerRevolution = 200;  // change this to match the number of steps per revolution for your stepper motor
const int totalSteps = 400; // the total steps the motor should move
Stepper myStepper(stepsPerRevolution, 4,5); // create a stepper object and specify the pins
int ldr1pin = A2;  // LDR1 connected to analog pin A0
int ldr2pin = A3;  // LDR2 connected to analog pin A1
int ldr1value = 0;  // variable to store the value of LDR1
int ldr2value = 0;  // variable to store the value of LDR2
int stepCount = 0;  // variable to store the step count
int stepsTaken = 0;  // variable to store the total steps taken

void setup() {
  myStepper.setSpeed(30); // set the speed of the stepper motor
}

void loop() {
  ldr1value = analogRead(ldr1pin);  // read the value of LDR1
  ldr2value = analogRead(ldr2pin);  // read the value of LDR2
  stepCount = abs(ldr1value - ldr2value) / 4;  // calculate the step count based on the difference of the LDR values
  stepCount = constrain(stepCount, 1, 50);  // constrain the step count between 1 and 50
  if(ldr1value > ldr2value) {
    myStepper.step(stepCount);  // rotate the stepper motor in the clockwise direction
  } else {
    myStepper.step(-stepCount);  // rotate the stepper motor in the counter-clockwise direction
  }
  stepsTaken += abs(stepCount); // add the step count to the total steps taken
  if (stepsTaken >= totalSteps) {
    myStepper.step(0);  // stop the stepper motor when it reaches the total steps
    stepsTaken = 0; // reset the steps taken variable
  }
  delay(15);  // delay for 15 milliseconds
}
