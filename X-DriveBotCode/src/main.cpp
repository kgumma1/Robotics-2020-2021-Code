/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// topSensor            line          D               
// bottomSensor         line          E               
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

vex::motor LeftIntake(vex::PORT17, true);
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
  auton();
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
int topSensorInit = 0;

void initializeSensor() {
  wait(5000, msec);
  topSensorInit = topSensor.value(vex::analogUnits::range12bit);
  while (1) {
    if (topSensor.value(vex::analogUnits::range12bit) > topSensorInit) {
      topSensorInit = topSensor.value(vex::analogUnits::range12bit) - 70;
    }
    //printf("sensorinit = %d\n", topSensorInit);
    wait(100, msec);
  }
}

vex::event startInitTop(initializeSensor);

void release() {
  if (ct.ButtonX.pressing()) {
    TopRoller.spinFor(180, vex::rotationUnits::deg, 20, vex::velocityUnits::pct, true);
    RightIntake.spinFor(180, vex::rotationUnits::deg, 20, vex::velocityUnits::pct, true);
    LeftIntake.spinFor(180, vex::rotationUnits::deg, 20, vex::velocityUnits::pct, true);
  }
}


void rollers() {
  // L1 = intake, L2 = outtake, otherwise stop
  // R2 = run intakes + rollers
  if(ct.ButtonL1.pressing()) {
    BottomRoller.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
    TopRoller.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
    TopRoller.setBrake(vex::brakeType::coast);
  } else if (ct.ButtonL2.pressing()) {
    BottomRoller.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
    TopRoller.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);
    TopRoller.setBrake(vex::brakeType::coast);
  } else if (ct.ButtonY.pressing()) {
    TopRoller.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
    TopRoller.setBrake(vex::brakeType::coast);
  } else if (ct.ButtonR2.pressing()) {
    BottomRoller.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
    if ((topSensorInit - topSensor.value(vex::analogUnits::range12bit)) < 30) {
      printf("diff = %ld\n", topSensorInit - topSensor.value(vex::analogUnits::range12bit));
      TopRoller.spin(vex::directionType::fwd, 3, vex::voltageUnits::volt);
    } else {
      TopRoller.stop(vex::brakeType::hold);
      TopRoller.setBrake(vex::brakeType::hold);
    }
  } else {
    BottomRoller.stop(vex::brakeType::coast);
    TopRoller.stop();
  }

}

void usercontrol(void) {
  // User control code here, inside the loop
  startInitTop.broadcast();

  while (1) {
    if(ct.ButtonLeft.pressing()) {
      auton();
    }
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

    release();

    //printf("sensor = %ld\n", topSensor.value(vex::analogUnits::range12bit));
    //printf("sensorinit = %d\n", topSensorInit);
 

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
