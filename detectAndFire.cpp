/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\harm26015                                        */
/*    Created:      Fri May 13 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// frontRMotor          motor         9               
// frontLMotor          motor         2               
// rangeFinderE         sonar         E, F            
// BumperC              bumper        C               
// angleArm             motor         11              
// ServoH               servo         H               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int stat = 0;
int timeSeen = 0;

int whenStarted1() {
  wait(1, msec);
  frontLMotor.setVelocity(20, percent);

  while (true) {
    frontLMotor.spin(forward);

    while (stat == 0);
    frontLMotor.stop();

    while (rangeFinderE.distance(inches) <= 61) {
      if (timeSeen >= 10) {
        angleArm.spinFor(forward, 37, degrees);
        wait(1500, msec);
        ServoH.setPosition(-120, degrees);
        break;
      } else {
        timeSeen++;
        wait(1000, msec);
      }
    }
  }

  return 0;
}

int whenStarted2() {
  frontRMotor.spinFor(forward, 0.1, degrees);
  frontRMotor.setVelocity(20, percent);
  while (true) {
    frontRMotor.spin(reverse);

    while (stat == 0);
    frontRMotor.stop();
    while(stat == 1);
  }

  return 0;
}

int whenStarted3() {
  angleArm.setVelocity(1, percent);
  while (stat == 0) {
    if (rangeFinderE.distance(inches) <= 61) {
      stat = 1;
    }
  }

  Brain.Screen.setFillColor(red);
  Brain.Screen.print("Too Close!");

  return 0;
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  task ws1(whenStarted2);
  task ws2(whenStarted3);
  whenStarted1();
}
