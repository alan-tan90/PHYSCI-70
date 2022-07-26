#include <AccelStepper.h>

const int stepPin = 11;  // blue
const int dirPin = 12;   // orange
int x;
const int rotationConstant = 52;

// Define a stepper and the pins it will use
AccelStepper stepper(1, stepPin, dirPin); // initialise accelstepper for a two wire board

void setup()
{
  x = 0;
  // Calibrate the thing
  if(stepper.distanceToGo() == 0)
  {
    stepper.moveTo(x);
  }
  stepper.run();
  delay(1500);
  Serial.begin(9600);
  Serial.println("Stepper Calibrated!");
}

void loop()
{
  if (stepper.distanceToGo() == 0)
  {
    x += rotationConstant - (rotationConstant * 4) * (x > (rotationConstant * 2));
    Serial.println("The Stepper is moving, and x = ");
    Serial.print(x);
    Serial.print(".\n");
    // Random change to speed, position and acceleration
    // Make sure we dont get 0 speed or accelerations
    delay(1000);
    stepper.moveTo(x);
    stepper.setMaxSpeed(900);
    stepper.setAcceleration(300);
  }
  stepper.run();
}