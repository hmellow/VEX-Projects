/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Harry                                                     */
/*    Created:      Mon May 16 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// servoH               servo         H               
// angleArm             motor         11              
// BumperC              bumper        C               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>

using namespace vex;

// Screen coordinates
int xPos;
int yPos;

// User-set range
int distSet = 0;

// Tested values
float testedAngle = 33.5;
float testedRange = 17.5;

// Calculating s-squared over g
float veloSqG = testedRange / (sin(2 * testedAngle));


int updateScreen(int val) {
  Brain.Screen.clearLine(1);
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print(val);

  return 0;
}

int calculateAngle(int range) {
  float theta = range / veloSqG;
  theta = (asin(theta)) / 2;

  return theta;
}

int fire(int dist) {
  // Account for starting angling of arm in degrees
  float angleCorrection = 3.5;

  // Amount to change arm angle
  float angling = (calculateAngle(dist)) - angleCorrection + 37;
  Brain.Screen.setCursor(7, 1);
  Brain.Screen.print(angling);

  // Firing sequence
  angleArm.spinFor(forward, angling, degrees);
  wait(1500, msec);
  while (true) {
    if (BumperC.pressing()) {
      servoH.setPosition(-120, degrees);

      while (BumperC.pressing());
    }
  }

  return 0;
}

int whenStarted1() {
  updateScreen(0);
  Brain.Screen.drawRectangle(10, 10, 100, 100, green);
  Brain.Screen.drawRectangle(20, 120, 75, 75, yellow);

  while (true) {
    xPos = Brain.Screen.xPosition();
    yPos = Brain.Screen.yPosition();

    while (Brain.Screen.pressing()) {
      // Green button
      if ((xPos >= 10 && xPos <= 110) && (yPos >= 10 && yPos <= 110)) {
        fire(distSet);
      }
      
      // Yellow button
      if ((xPos >= 20 && xPos <= 95) && (yPos >= 120 && yPos <= 195)) {
        distSet++;
        updateScreen(distSet);
      }

      // Wait for screen release
      while (Brain.Screen.pressing());
    }
  }

  return 0;
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  whenStarted1();
}
