#include <Arduino.h>
#include <AccelStepper.h>

#define dirPin 4
#define stepPin 5
#define motorInterfaceType 1


AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);


void setup() {
  // put your setup code here, to run once:
    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(100);
    stepper.setSpeed(50);
}

void loop() {
  // put your main code here, to run repeatedly:
    stepper.moveTo(-1000);
    // Run to target position with set speed and acceleration/deceleration:
    stepper.runToPosition();

    delay(100);

    // Move back to zero:
    // stepper.moveTo(0);
    // stepper.runToPosition();
}