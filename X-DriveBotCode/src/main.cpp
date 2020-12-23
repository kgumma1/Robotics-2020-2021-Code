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

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
vex::motor LeftFront    = vex::motor(vex::PORT5, true);
vex::motor LeftRear     = vex::motor(vex::PORT4, true);
vex::motor RightFront   = vex::motor(vex::PORT8);
vex::motor RightRear    = vex::motor(vex::PORT10);

vex::motor LeftIntake   = vex::motor(vex::PORT11, true);
vex::motor RightIntake  = vex::motor(vex::PORT18);

vex::motor BottomRoller = vex::motor(vex::PORT7, true);
vex::motor TopRoller = vex::motor(vex::PORT16, true);

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

int printTimer=0;

const double PI = 3.14159265;
const double PROPORTIONFACTOR = 200.0 / 90.0;

void spinRightMotors(double speedPerc) { 
  LeftFront.spin(vex::directionType::fwd, speedPerc, vex::velocityUnits::pct);
  RightRear.spin(vex::directionType::fwd, speedPerc, vex::velocityUnits::pct);
}

void spinLeftMotors(double speedPerc) {
  RightFront.spin(vex::directionType::fwd, speedPerc, vex::velocityUnits::pct);
  LeftRear.spin(vex::directionType::fwd, speedPerc, vex::velocityUnits::pct);
}

double calcPower(double val1, double val2, double powerReduction) {
  double stickAngle;
  stickAngle = atan(val1 / val2) * (180 / PI);
  return ((stickAngle * PROPORTIONFACTOR) - 100) * powerReduction;
}

int isPos(double num) {
  if(num >= 0) {
    return 1;
  } else {
    return -1;
  }
}

double roundNum(double number,  double posTarget, int threshold) {
  if (fabs(fabs(number) - posTarget) <= threshold) {
    return 45 * isPos(number);
  } else {
    return number;
  }
}

double expFunction(double num) {
  if (num < 0) {
    num*=-1;
  }
  num = 0.5108 * pow(1.0471, (num + 15)) - 1.0188;
  return num;
}

double getMotorSpeed(vex::motor motorName) {
  return motorName.velocity(vex::velocityUnits::pct);
}

double findMin(double motorValues[]) {
  double min = motorValues[0];
  for (int i = 0; i < 4; i++) {
    if(motorValues[i] < min) {
      min = motorValues[i];
    }
  }
  return min;
}

double findMax(double motorValues[]) {
  double max = motorValues[0];
  for (int i = 0; i < 4; i++) {
    if(motorValues[i] > max) {
      max = motorValues[i];
    }
  }
  return max;
}

double findAvg(double motorValues[]) {
  double sum = 0;
  for (int i = 0; i < 4; i++) {
    sum += motorValues[i];
  }
  return sum / 4;
}

void drive() {
  
  //update stick positions
  int leftStickX = ct.Axis4.position();
  int leftStickY = ct.Axis3.position();
  int rightStickX = ct.Axis1.position();
  int decelerateSpeed = 10;
  
  double powerLeftGroup = 0; 
  double powerRightGroup = 0;
  double powerReduction = 1;

  double motorValues[] = {getMotorSpeed(LeftFront), getMotorSpeed(RightFront), getMotorSpeed(LeftRear), getMotorSpeed(RightRear)};
  double forwardSpeed = findMin(motorValues);
  double averageSpeed = findAvg(motorValues);
  double maxSpeed = findMax(motorValues);

  powerReduction = expFunction( sqrt( pow(leftStickX, 2) + pow(leftStickY, 2) ) ) / 100;
  //powerReduction = sqrt( pow(leftStickX, 2) + pow(leftStickY, 2) ) / 100;
    
  if(abs(rightStickX) > 5) {
    //used when a spinning motion is desired
    rightStickX = expFunction(rightStickX) * isPos(rightStickX);

    LeftFront.spin(vex::directionType::fwd, rightStickX, vex::velocityUnits::pct);
    LeftRear.spin(vex::directionType::fwd, rightStickX, vex::velocityUnits::pct);
    RightFront.spin(vex::directionType::fwd, -rightStickX, vex::velocityUnits::pct);
    RightRear.spin(vex::directionType::fwd, -rightStickX, vex::velocityUnits::pct);

   
  } else if (abs(leftStickX) <= 10 && abs(leftStickY) <= 10) {
    /*// decelerate code
    if (getMotorSpeed(LeftFront) > decelerateSpeed) {
      spinRightMotors(getMotorSpeed(LeftFront) - decelerateSpeed);
    } else if (getMotorSpeed(LeftFront) < -decelerateSpeed) {
      spinRightMotors(getMotorSpeed(LeftFront) + decelerateSpeed);
    } else {
      spinRightMotors(0);
    }

    if (getMotorSpeed(RightFront) > decelerateSpeed) {
      spinLeftMotors(getMotorSpeed(RightFront) - decelerateSpeed);
    } else if (getMotorSpeed(RightFront) < -decelerateSpeed) {
      spinLeftMotors(getMotorSpeed(RightFront) + decelerateSpeed);
    } else {
      spinRightMotors(0);
    }*/
    spinRightMotors(0);
    spinLeftMotors(0);
    
  } else if(abs(leftStickX) <= 10) {
    if (fabs(double(leftStickY) - averageSpeed) < 10) {
      spinRightMotors(100 * powerReduction * (forwardSpeed - 5));
      spinLeftMotors(100 * powerReduction * (forwardSpeed - 5));
    } else {
    spinRightMotors(100 * powerReduction * isPos(leftStickY));
    spinLeftMotors(100 * powerReduction * isPos(leftStickY));
    }

    /* alt code
    if (fabs(getMotorSpeed(LeftFront) - getMotorSpeed(RightRear)) < 5) {
      spinRightMotors(100 * powerReduction * (forwardSpeed - 5));
    } else {
      spinRightMotors(100 * powerReduction * isPos(leftStickY));
    }

    if (fabs(getMotorSpeed(RightFront) - getMotorSpeed(LeftRear)) < 5) {
      spinLeftMotors(100 * powerReduction * (forwardSpeed - 5));
    } else {   
      spinLeftMotors(100 * powerReduction * isPos(leftStickY));
    }*/


  } else if(abs(leftStickY) <= 10) {
    spinRightMotors(100 * powerReduction * isPos(leftStickX));
    spinLeftMotors(-100 * powerReduction * isPos(leftStickX)); 

  } else {
      
    if (leftStickX >= 0 && leftStickY >= 0) {
      //stickAngle = atan(leftStickY / leftStickX) * (180 / PI);
      //powerLeftGroup = ((stickAngle * PROPORTIONFACTOR) - 100) * powerReduction;
      powerLeftGroup = calcPower(leftStickY, leftStickX, powerReduction);
      powerRightGroup = 100 * powerReduction;
        
    } else if (leftStickX <= 0 && leftStickY >= 0) {
      //stickAngle = atan(leftStickY / leftStickX) * (180 / PI);
      //powerRightGroup = ((stickAngle * PROPORTIONFACTOR) - 100) * powerReduction;
      powerRightGroup = calcPower(leftStickY, leftStickX, powerReduction);
      powerLeftGroup = 100 * powerReduction;

    } else if (leftStickX >= 0 && leftStickY <= 0) {
      //stickAngle = atan(leftStickX / leftStickY) * (180 / PI);
      //powerRightGroup = ((stickAngle * PROPORTIONFACTOR) - 100) * powerReduction;
      powerRightGroup = calcPower(leftStickX, leftStickY, powerReduction);
      powerLeftGroup = -100 * powerReduction;

    } else if (leftStickX <= 0 && leftStickY <= 0) {
      //stickAngle = atan(leftStickX / leftStickY) * (180 / PI);
      //powerLeftGroup = ((stickAngle * PROPORTIONFACTOR) - 100) * powerReduction;
      powerLeftGroup = calcPower(leftStickX, leftStickY, powerReduction);
      powerRightGroup = -100 * powerReduction;

    }

    //powerRightGroup = roundNum(powerRightGroup, 0, 10);
    //powerLeftGroup = roundNum(powerLeftGroup, 0, 10);

    printf("right = %f", powerRightGroup);
    printf(" left = %f/n", powerLeftGroup);

    spinRightMotors(powerRightGroup);
    spinLeftMotors(powerLeftGroup);
      
  }

}

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
