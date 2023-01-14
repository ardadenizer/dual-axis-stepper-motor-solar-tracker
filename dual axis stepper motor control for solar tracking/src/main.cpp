#include <Arduino.h>
#include <AccelStepper.h>
// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 4
#define stepPin 5
#define motorInterfaceType 1

int state = true;
int value = digitalRead(2);

// Definition of function prototypes:
void switchInterrupt (void);

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  // Set the maximum speed and acceleration:
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
  stepper.setSpeed(50);
  attachInterrupt(digitalPinToInterrupt(2), switchInterrupt, FALLING);
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  
}

void loop() {
  while (state){
    // Set the target position:
    Serial.println(value);
    
    stepper.moveTo(3000);
    // Run to target position with set speed and acceleration/deceleration:
    stepper.runToPosition();

    delay(100);

    // Move back to zero:
    stepper.moveTo(0);
    stepper.runToPosition();

    delay(100);
  }
}
void switchInterrupt (){
  stepper.stop();
  //delay(1000);
  state = false;

  }
