/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

//#include "setup.cpp"
#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

vex::motor LeftFront(vex::PORT5, true);
vex::motor LeftRear(vex::PORT4, true);
vex::motor RightFront(vex::PORT8);
vex::motor RightRear(vex::PORT10);

vex::motor LeftIntake(vex::PORT11, true);
vex::motor RightIntake(vex::PORT18);

vex::motor BottomRoller(vex::PORT7, true);
vex::motor TopRoller(vex::PORT16, true);

vex::controller ct;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/



void intake(){
  // R1 = run intakes
  // R2 = run intakes + rollers
  if (ct.ButtonR1.pressing() || ct.ButtonR2.pressing()) {
    LeftIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    RightIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    } else if (ct.ButtonRight.pressing()){
    //LeftIntake.spin(vex::directionType::rev, intakespeed, vex::velocityUnits::pct);
    //RightIntake.spin(vex::directionType::rev, intakespeed, vex::velocityUnits::pct);
    LeftIntake.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);
    RightIntake.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);
    } else {
     LeftIntake.stop(vex::brakeType::hold);
     RightIntake.stop(vex::brakeType::hold);
   }
}

void rollers() {
  // L1 = intake, L2 = outtake, otherwise stop
  // R2 = run intakes + rollers
  if(ct.ButtonL1.pressing() || ct.ButtonR2.pressing()) {
    BottomRoller.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
    TopRoller.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
  } else if (ct.ButtonL2.pressing()) {
    BottomRoller.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
    TopRoller.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);
  } else {
    BottomRoller.stop(vex::brakeType::hold);
    TopRoller.stop(vex::brakeType::hold);
  }

}



void syncRatchet() {
  // turn motor until it starts struggling, then stop
  spinMotor(LeftIntake, -20);
  while(getMotorSpeed(LeftIntake) > -10){
    continue;
  }
  LeftIntake.stop(vex::brakeType::coast);

  spinMotor(RightIntake, -20);
  while(getMotorSpeed(RightIntake) > -10){
    continue;
  }
  RightIntake.stop(vex::brakeType::coast);
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    drive();

    intake();

    rollers();


    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
