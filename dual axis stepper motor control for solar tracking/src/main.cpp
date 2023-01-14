#include <Arduino.h>
#include <AccelStepper.h>
// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 4
#define stepPin 5
#define motorInterfaceType 1

// Global variables 
int loopState = true; // while loop state for terminating the program. 
volatile int switchValue = digitalRead(2);
long int stepPos = 0;
unsigned long int stepCounter = 0;
unsigned int max_step = 4000;
bool loop_flag_break = false; // loop flag responsible of for loop breaking for position setting 

// Definition of function prototypes:
void switchInterrupt (void);

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  
   Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(2), switchInterrupt, FALLING);

  pinMode(2,INPUT_PULLUP);
  
  // Set the maximum speed and acceleration:
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
  stepper.setSpeed(50);

  // Initialization: setting stepper to the switch position and making it stay in 90 degrees

  
}

void loop() {

  while (true){
  
  // Set the target position:
  // Serial.println(switchValue);
  
  // Pos 1600: 90 degrees , 3200: 180 degrees at 1/8 , -ve value means reverse direction
  Serial.println("Entering into the for loop");

  for (stepCounter = 1; stepCounter <= max_step; stepCounter++ ){
    stepper.moveTo(-stepCounter);
    stepper.runToPosition();

    Serial.println(-stepCounter);


    if (loop_flag_break == true) break;
  }
  // Moving to flat position 
  stepper.moveTo(1600);
  // Run to target position with set speed and acceleration/deceleration:
  stepper.runToPosition();
  delay(200);

  Serial.println("Program is finished. The panel pos shall be flat");
  stepper.stop();
  break;
  }
}
void switchInterrupt (){
    //stepper.stop();
    stepper.setCurrentPosition(0);
    loop_flag_break = true;

  }
