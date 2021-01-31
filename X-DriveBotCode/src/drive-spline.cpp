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

double accelCap(double num, double currVelocity, bool active) {
  /* cap */
  // keep in range 1.0 - 1.7
  // changes how much of a difference in speed and wanted speed
  // is required in order to activate acceleration or just run
  // the motor at wanted speed
  // higher cap = less sluggish, more drift/spin
  // lower cap = effects of accelSpeed are magnified

  /* accelSped */
  // keep in range 1 - 15
  // changes the speed of acceleration
  // higher number = accelerate faster, may drift/spin
  // lower number = more sluggish, less drift/spin 

  // reccomendation - only mess with accelSpeed

  double cap = 1.2; 
  double accelSpeed = 8;
  if (num > 0 && active) {
    if (num > currVelocity * cap) {
      return (currVelocity + accelSpeed) * cap;
    } else {
      return num;
    }
  } else if (active) {
    if (num < currVelocity * cap) {
      return (currVelocity - accelSpeed) * cap;
    } else {
      return num;
    }
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

  double reductionAmount = 0;
  double speedLF = getMotorSpeed(LeftFront);
  double speedLR = getMotorSpeed(LeftRear);
  double speedRF = getMotorSpeed(RightFront);
  double speedRR = getMotorSpeed(RightRear);


  
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


    bool notspinning = false;
    if (rightStickX == 0) {
      notspinning = true;
    }

    bool goingStraight = false;
    if (leftStickX == 0) {
      goingStraight = true;
    }

    double inputLF = accelCap(round100(powerRightGroup + rightStickX), speedLF, notspinning);
    double inputRR = accelCap(round100(powerRightGroup - rightStickX), speedRR, notspinning);
    double inputLR = accelCap(round100(powerLeftGroup + rightStickX), speedLR, notspinning);
    double inputRF = accelCap(round100(powerLeftGroup - rightStickX), speedRF, notspinning);


    /*
    double motorvalues[] = {speedLF, speedRR, speedLR, speedRF};

    double min = 100;
    double max = -100;

    for (int i = 0; i < 4; i++) {
      if (motorvalues[i] > max) {
          max = motorvalues[i];
      }
      if (motorvalues[i] < min) {
          min = motorvalues[i];
      }
    }

    int threshold = 5;
    if (goingStraight && min > 0) {
      if (speedLF > min + threshold) {
        inputLF = min/inputLF;
      }
      if (speedLR > min + threshold) {
        inputLR = min/inputLR;
      }
      if (speedRR > min + threshold) {
        inputRR = min/inputRR;
      }
      if (speedRF > min + threshold) {
        inputRF = min/inputRF;
      }      
    } else if (goingStraight) {
      if (speedLF < max - threshold) {
        inputLF = max/inputLF;
      }
      if (speedLR < max - threshold) {
        inputLR = max/inputLR;
      }
      if (speedRR < max - threshold) {
        inputRR = max/inputRR;
      }
      if (speedRF < max - threshold) {
        inputRF = max/inputRF;
      }      
    }*/

    spinMotor(LeftFront, inputLF);
    spinMotor(RightRear, inputRR);
    spinMotor(LeftRear, inputLR);
    spinMotor(RightFront, inputRF);
    




  } else {
    LeftFront.stop(vex::brakeType::coast);
    RightFront.stop(vex::brakeType::coast);
    LeftRear.stop(vex::brakeType::coast);
    RightRear.stop(vex::brakeType::coast);
  }

}