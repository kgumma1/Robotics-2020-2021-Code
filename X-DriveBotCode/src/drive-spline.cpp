#include "vex.h"

using namespace vex;

int printTimer=0;

const double PI = 3.14159265;
const double PROPORTION_FACTOR = 200.0 / 90.0;

void spinMotor(vex::motor motorName, double speedPerc) {
  motorName.spin(vex::directionType::fwd, speedPerc, vex::velocityUnits::pct);
}

double calcPower(double val1, double val2, double powerReduction) {
  double stickAngle;
  stickAngle = atan(val1 / val2) * (180 / PI);
  return ((stickAngle * PROPORTION_FACTOR) - 100) * powerReduction;
}


int isPos(double num) {
  if(num >= 0) {
    return 1;
  } else {
    return -1;
  }
}

double expFunction(double num) {
  if (num < 0) {
    num*=-1;
  }
  num = 0.1108 * pow(1.061, (num + 15)) - 0.2698;
  return num;
}

double getMotorSpeed(vex::motor motorName) {
  return motorName.velocity(vex::velocityUnits::pct);
}

double round100(double num) {
  if(num > 100) {
    return 100;
  } else if (num < -100) {
    return -100;
  } else {
    return num;
  }
}

void drive() {
  
  //update stick positions
  int leftStickX = ct.Axis4.position();
  int leftStickY = ct.Axis3.position();
  int rightStickX = ct.Axis1.position();
  
  double powerLeftGroup = 0; 
  double powerRightGroup = 0;
  double powerReduction = 1;

  powerReduction = expFunction( sqrt( pow(leftStickX, 2) + pow(leftStickY, 2) ) ) / 100;


  
  if ((abs(leftStickX) >= 20 || abs(leftStickY) >= 20) || abs(rightStickX) > 5) {
    if (abs(leftStickX) < 25) {
      leftStickX = 0;
    }

    if(abs(leftStickY) < 10) {
      leftStickY = 0;
    }

    rightStickX = expFunction(rightStickX) * isPos(rightStickX) / 2;
    

    if (leftStickX >= 0 && leftStickY >= 0) {
      powerLeftGroup = calcPower(leftStickY, leftStickX, powerReduction);
      powerRightGroup = 100 * powerReduction;
        
    } else if (leftStickX <= 0 && leftStickY >= 0) {
      powerRightGroup = calcPower(leftStickY, leftStickX, powerReduction);
      powerLeftGroup = 100 * powerReduction;

    } else if (leftStickX >= 0 && leftStickY <= 0) {
      powerRightGroup = calcPower(leftStickX, leftStickY, powerReduction);
      powerLeftGroup = -100 * powerReduction;

    } else if (leftStickX <= 0 && leftStickY <= 0) {
      powerLeftGroup = calcPower(leftStickX, leftStickY, powerReduction);
      powerRightGroup = -100 * powerReduction;

    }

    
    spinMotor(LeftFront, round100(powerRightGroup + rightStickX));
    spinMotor(RightRear, round100(powerRightGroup - rightStickX));
    spinMotor(LeftRear, round100(powerLeftGroup + rightStickX));
    spinMotor(RightFront, round100(powerLeftGroup - rightStickX));
  } else {
    LeftFront.stop(vex::brakeType::coast);
    RightFront.stop(vex::brakeType::coast);
    LeftRear.stop(vex::brakeType::coast);
    RightRear.stop(vex::brakeType::coast);
  }

}