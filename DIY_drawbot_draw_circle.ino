/* 
This Arduino sketch was written for an article in the May 2025 issue of Make: Magazine.
This sketch is an example for the DIY drawbot. In this example, the points needed to draw
a circle are calculated and sent to the servos of the DIY drawbot.

Author: Matt Eaton
www.MattEaton.info

Licence: (MIT) fully open-source.  Feel free to edit, copy, update, etc. Have fun!
For more information about learning inverse kinematics for robotics projects, feel
free to check out my book, also published through Make entitled "Make: Robotic Arms" 
available on Amazon, through Make's website, and other popular book retailers.
*/

#include "Servo.h"
Servo servoOne;
Servo servoTwo;
double x = 40.0;
double y = 120.0;
double linkOne = 100.0;
double linkTwo = 100.0;
double alphaOne;
double alphaTwo;
double alphaFinal;
double betaOne;
double betaTwo;
double betaFinal;
double c;
double d = 80.0;
double e;
const int circlePoints = 36; // Number of points in the circle (e.g., 36 points for a 10-degree increment)
double radius = 30.0; // Radius of the circle (half of the diameter)
double centerX = 40.0; // X coordinate of the circle center
double centerY = 140.0; // Y coordinate of the circle center

void setup() {
  Serial.begin(9600);
  servoOne.attach(3);
  servoTwo.attach(5);
}

void loop() 
{
  for (int i = 0; i < circlePoints; i++) {
    double angle = (2 * PI / circlePoints) * i;
    x = centerX + radius * cos(angle);
    y = centerY + radius * sin(angle);
    
    c = sqrt((x * x) + (y * y));
    e = sqrt(((d - x) * (d - x)) + (y * y));
    alphaOne = atan(y / x) * (180 / PI);
    alphaTwo = acos(((linkTwo * linkTwo) - (c * c) - (linkOne * linkOne)) / (-2 * linkOne * c)) * (180 / PI);

    betaOne = atan(y / (d - x)) * (180 / PI);
    betaTwo = acos(((linkTwo * linkTwo) - (e * e) - (linkOne * linkOne)) / (-2 * linkOne * e)) * (180 / PI);

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

    servoOne.write(alphaFinal);
    servoTwo.write(betaFinal);
    
    delay(10); // Adjust the delay as needed for smooth motion
  }
}
