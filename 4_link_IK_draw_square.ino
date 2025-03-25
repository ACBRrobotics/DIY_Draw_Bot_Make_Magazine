// A simple Arduino sketch for calculating the inverse kinematics
// of a 4 Link Dual SCARA robot arm.

// These four values are just sample values and can be changed to accommodate the
// values of your system.
#include "ServoEasing.hpp"
ServoEasing Servo1;
ServoEasing Servo2;
#define SERVO1_PIN 9
#define SERVO2_PIN 10
double x = -10.0;
double y = 85.0;
double linkOne = 50.0;
double linkTwo = 100.0;
double alphaOne;
double alphaTwo;
double alphaFinal;
double betaOne;
double betaTwo;
double betaFinal;
double c;
double d = 60.0;
double e;

void setup() {
  Serial.begin(9600);
  Servo1.attach(SERVO1_PIN); // Attach Servo1 to pin 9
  Servo2.attach(SERVO2_PIN); // Attach Servo2 to pin 10
  Servo1.write(180); // Start Servo1 at 90 degrees
  Servo2.write(90); // Start Servo2 at 90 degrees
  setSpeedForAllServos(10); // 30 degrees per second
}

void loop() 
{
  // Define the four corners of the square
  double points[30][2] = {
    {-10,90},
    {-5,90},
    {-5,120},
    {5,120},
    {5,100},
    {5,120},
    {15,120},
    {15,90},
    {20,90},
    {20,120},
    {35,120},
    {35,100},
    {20,100},
    {35,100},
    {35,90},
    {40,90},
    {40,120},
    {40,100},
    {50,120},
    {40,100},
    {50,90},
    {55,90},
    {55,120},
    {65,120},
    {55,120},
    {55,100},
    {65,100},
    {55,100},
    {55,90},
    {65,90}
  };

  // Move through each corner of the square
  delay(5000);
  for (int i = 0; i < 30; i++) {
    x = points[i][0];
    y = points[i][1];
    
    c = sqrt((x * x) + (y * y));
    e = sqrt(((d - x) * (d - x)) + (y * y));
    alphaOne = atan(y / x) * (180 / PI);
    alphaTwo = acos(((linkTwo * linkTwo) - (c * c) - (linkOne * linkOne)) 
                   / (-2 * linkOne * c)) * (180 / PI);

    betaOne = atan(y / (d - x)) * (180 / PI);
    betaTwo = acos(((linkTwo * linkTwo) - (e * e) - (linkOne * linkOne)) 
                  / (-2 * linkOne * e)) * (180 / PI);

    if (x < 0) {
      alphaFinal = 180 + ((alphaOne) + (alphaTwo));
      betaFinal = 180 - ((betaOne) + (betaTwo));
    }
    else if (x > d) {
      alphaFinal = ((alphaOne) + (alphaTwo));
      betaFinal = -1 * ((betaOne) + (betaTwo));
    }
    else {
      alphaFinal = ((alphaOne) + (alphaTwo));
      betaFinal = 180 - ((betaOne) + (betaTwo));
    }

    Serial.print("alpha One: ");
    Serial.print(alphaOne);
    Serial.print(" beta One:");
    Serial.print(betaOne);
    Serial.print(" alpha Two: ");
    Serial.print(alphaTwo);
    Serial.print(" beta Two:");
    Serial.print(betaTwo);
    Serial.print(" Alpha: ");
    Serial.print(alphaFinal);
    Serial.print(" Beta: ");
    Serial.println(betaFinal);

    Servo1.setEaseTo((int)alphaFinal);
    Servo2.setEaseTo((int)betaFinal);
    synchronizeAllServosStartAndWaitForAllServosToStop(); // Ensure simultaneous motion

    //delay(1000); // Adjust the delay as needed for smooth motion between points
  }
}
