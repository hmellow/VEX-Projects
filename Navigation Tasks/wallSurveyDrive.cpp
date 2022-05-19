/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\harm26015                                        */
/*    Created:      Fri Apr 15 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// frontRMotor          motor         9               
// frontLMotor          motor         2               
// BumperC              bumper        C               
// ServoG               servo         G               
// angleArm             motor         11              
// rangeFinderE         sonar         E, F            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// # of degrees to turn back wheels for a 180 deg turn
int turnAround = 1800;
float halfTurn = turnAround/2;
// Number of degrees to turn for a foot
int foot = 1040;
int swit = 0;

// Status (idle or active)
int stat = 0;
// Number of times button pressed
int timesPressed = 0;

// Variables for correction
int standard = 75;
float current = standard;

// Touchscreen position
int xPos;
int yPos;

// Temporary
int xPos2;
int yPos2;


int updateScreen(int n) {
  Brain.Screen.clearLine(11);
  Brain.Screen.setCursor(11,5);
  Brain.Screen.print("n:");
  Brain.Screen.setCursor(11, 8);
  Brain.Screen.print(n);
  return 0;
}

int fCheck() {
  wait(5, msec);
  // Difference in rotation distance
  float correction;
  // Dampen correction value for velocity change
  float dampen = 0.21;
  // Delay between iterations
  float delay = 0;

  while (swit == 0) {
    // float rotationsR = frontRMotor.position(degrees);
    // float rotationsL = frontLMotor.position(degrees);

    // Distance correction
    int wall = rangeFinderE.distance(inches);

    correction = (7 - wall) * dampen * -1;
    current = standard + correction;
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print(correction);
    wait(delay, msec);
  }
  // turn
  //frontLMotor.spinFor(forward, turnAround, degrees);
  //frontRMotor.stop();
  return 0;
}

int updateTurn(int dist) {
  frontLMotor.setVelocity(standard, percent);
  frontRMotor.setVelocity(standard, percent);

  while ((frontRMotor.position(degrees)) < (foot * dist)) {
    frontLMotor.setVelocity(current, percent);
    wait(1, msec);
  }
  swit = 1;
  // turn
  //frontRMotor.spinFor(reverse, turnAround, degrees);
  //frontLMotor.stop();
  return 0;
}


// Iteration control
int whenStarted1() {
  wait(1, msec);
  frontLMotor.spin(forward);
  fCheck();
  frontLMotor.stop();

  return 0;
}

int whenStarted2() {
  frontRMotor.spin(forward);
  updateTurn(50);
  frontRMotor.stop();

  return 0;
}

int whenStarted3() {
  
  return 0;
}



int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

task ws1(whenStarted2);
task ws2(whenStarted3);
whenStarted1();
}

