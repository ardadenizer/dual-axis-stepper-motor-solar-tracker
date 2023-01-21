#include <Arduino.h>
#include <AccelStepper.h>


#define dirPin 4
#define stepPin 5
#define motorInterfaceType 1

long int number = -1000;

 AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  // put your setup code here, to run once:
 

  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
  stepper.setSpeed(50);

  attachInterrupt(digitalPinToInterrupt(2), switchInterrupt, FALLING);

  pinMode(2,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  stepper.moveTo(number);
  stepper.runToPosition();
  stepper.stop();
}

void switchInterrupt(){

  stepper.stop();
  stepper.setCurrentPosition(0);

  number = 0;
  
}