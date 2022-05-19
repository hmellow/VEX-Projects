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
// angleArm             motor         11              
// frontRMotor          motor         9               
// frontLMotor          motor         2               
// BumperC              bumper        C               
// RangeFinderE         sonar         E, F            
// ServoH               servo         H               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int whenStarted1() {
  angleArm.setVelocity(1, percent);
  angleArm.spinFor(forward, 19, degrees);
  wait(1000, msec);
  ServoH.setPosition(-120, degrees);
  return 0;
}

int whenStarted2() {
  return 0;
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  task ws1(whenStarted2);
  whenStarted1();
}
