#include <Arduino.h>
#include <Stepper.h>


int analogPin3 = A3;
int analogPin4 = A4;
int analogPin2 = A2;
int analogPin1 = A1;

const int stepsPerRevolution = 600;

Stepper myStepper(stepsPerRevolution, 4,5);

 
  
void setup() {
  Serial.begin(9600);           //  setup serial
  myStepper.setSpeed(200);
}

void loop() {
  volatile int bottom_right_val = analogRead(analogPin3);
  bottom_right_val =  map (bottom_right_val, 0 , 1023, 0, 255 );

  volatile int top_right_val = analogRead(analogPin4);
  top_right_val =  map (top_right_val, 0 , 1023, 0, 255 );

  volatile int bottom_left_val = analogRead(analogPin2);
  bottom_left_val =  map (bottom_left_val, 0 , 1023, 0, 255 );

  volatile int top_left_val  = analogRead(analogPin1);
  top_left_val =  map (top_left_val, 0 , 1023, 0, 255 );  
    // read the input pin
  Serial.print("Bottom Right: ");
  Serial.println(bottom_right_val); 

  Serial.print("Top Right   : "); 
  Serial.println(top_right_val);

  Serial.print("Bottom Left : ");
  Serial.println(bottom_left_val);

  Serial.print("Top Left    : "); 
  Serial.println(top_left_val);

  delay (1000);

   Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay (1000);
   myStepper.step(0);
  delay(1000);
  myStepper.step(stepsPerRevolution);

}