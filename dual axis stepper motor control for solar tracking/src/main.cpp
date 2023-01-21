#include <Stepper.h>
#include <Arduino.h>

const int stepsPerRevolution = 200; // change this to match the number of steps per revolution for your stepper motor
const int topRight = A4;
const int topLeft = A1; // Top left LDR
const int bottomRight = A3;
const int bottomLeft = A2;
const int voltPin = A0;
 
const int maxStepCountVertical = 1160; // maximum step count limit for the stepper motor
const int maxStepCountHorizontal = 500;
int stepCountVertical = 0; // current step count
int stepCountHorizontal = 0;

// Definitions for voltage measurement
float adcVoltage = 0;
float inputVoltage = 0;

// Resistor value definitions

float R1 = 30000.0;
float R2 = 7500.0;

float refVoltage = 5.0;




Stepper motorVertical(stepsPerRevolution,8,9); // create a stepper object
Stepper motorHorizontal(stepsPerRevolution,4,5); // create a stepper object

void setup() {
  motorVertical.setSpeed(70); // set the speed of the stepper motor
  motorHorizontal.setSpeed(70);
  Serial.begin(9600);
}

void loop() {
  volatile int topLeftVal = analogRead(topLeft);
  volatile int topRightVal = analogRead(topRight);
  volatile int bottomRightVal = analogRead(bottomRight);
  volatile int bottomLeftVal = analogRead(bottomLeft);

  volatile int verticalDiff = (topRightVal + bottomRightVal) - (topLeftVal + bottomLeftVal);
  volatile int horizontalDiff = (topLeftVal + bottomLeftVal) - (topRightVal + bottomRightVal); 

  // volatile int  adcValue = analogRead(voltPin);

  // adcVoltage = (adcValue * refVoltage) / 1024.0;
  // inputVoltage = adcVoltage / (R2 / (R1 + R2));

  // Serial.print("Input voltage =");
  // Serial.println(inputVoltage,2);

  

   if (horizontalDiff > 0 && stepCountHorizontal < maxStepCountHorizontal) {
    // move clockwise
    motorHorizontal.step(1);
    stepCountHorizontal++;
  } else if (horizontalDiff < 0 && stepCountHorizontal > -maxStepCountHorizontal) {
    // move counter-clockwise
    motorHorizontal.step(-1);
    stepCountHorizontal--;
  }
  if (verticalDiff > 0 && stepCountVertical < maxStepCountVertical) {
    // move clockwise
    motorVertical.step(1);
    stepCountVertical++;
  } else if (verticalDiff < 0 && stepCountVertical > -maxStepCountVertical) {
    // move counter-clockwise
    motorVertical.step(-1);
    stepCountVertical--;
  }
 
  // delay is added to slow down the stepper motor and make it more visible
 // delay(50);
}
