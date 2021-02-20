#include "vex.h"

using namespace vex;

int printTimer=0;

const double PI = 3.14159265;
const double PROPORTION_FACTOR = 200.0 / 90.0;

void spinMotor(vex::motor motorName, double speedPerc) {
  motorName.spin(vex::directionType::fwd, speedPerc, vex::velocityUnits::pct);
}




int isPos(double num) {
  if(num >= 0) {
    return 1;
  } else {
    return -1;
  }
}

double calcPower(double val1, double val2, double powerReduction, int flipQuadrants = 1) {
  double stickAngle;
  if(fabs(val2) == 0) {
    val2 = 1 * isPos(val2);
  }
  stickAngle = atan(val1 / val2) * (180 / PI);
  return ((stickAngle * PROPORTION_FACTOR) - 100 * flipQuadrants) * powerReduction * flipQuadrants;
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

double distanceFromOrigin(double x, double y) {
  return sqrt( pow(x, 2) + pow(y, 2));
}

double calcPowerReduction(double leftStickX, double leftStickY) {
  if(leftStickX == 0 && leftStickY == 0) {
    return 0;
  }
  double maxX = 100 * cos(atan(leftStickY/leftStickX));
  double maxY = 100 * sin(atan(leftStickY/leftStickX));


  return expFunction( (distanceFromOrigin(leftStickX, leftStickY) / distanceFromOrigin(maxX, maxY)) * 100) / 100;
}

double accelCap(double num, double currVelocity, bool active) {
  return num;
  /* cap */
  // keep in range 1.0 - 1.7
  // changes how much of a difference in speed and wanted speed
  // is required in order to activate acceleration or just run
  // the motor at wanted speed
  // higher cap = less sluggish, more drift/spin
  // lower cap = effects of accelSpeed are magnified

  /* accelSpeed */
  // keep in range 1 - 15
  // changes the speed of acceleration
  // higher number = accelerate faster, may drift/spin
  // lower number = more sluggish, less drift/spin 

  // reccomendation - only mess with accelSpeed

  double cap = 1.5; 
  double accelSpeed = 10;
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

double encoderLeftInit = leftEncoder.position(vex::rotationUnits::deg);
double encoderRightInit = rightEncoder.position(vex::rotationUnits::deg);

void drive() {
  
  //update stick positions
  int leftStickX = ct.Axis4.position();
  int leftStickY = ct.Axis3.position();
  int rightStickX = ct.Axis1.position();
  
  double powerLeftGroup = 0; 
  double powerRightGroup = 0;
  double powerReduction = 1;

  powerReduction = calcPowerReduction(leftStickX, leftStickY);

  double reductionAmount = 0;
  double speedLF = getMotorSpeed(LeftFront);
  double speedLR = getMotorSpeed(LeftRear);
  double speedRF = getMotorSpeed(RightFront);
  double speedRR = getMotorSpeed(RightRear);


  
  if ((abs(leftStickX) >= 10 || abs(leftStickY) >= 10) || abs(rightStickX) > 5) {
    if (abs(leftStickX) < 10) {
      leftStickX = 0;
    }

    if(abs(leftStickY) < 10) {
      leftStickY = 0;
    }

    double turningSensitivity = 1.5;

    if(leftStickX > 50 || leftStickY > 50) {
      turningSensitivity = 1;
    }
    rightStickX = expFunction(rightStickX) * isPos(rightStickX) / turningSensitivity;
    

    if (leftStickX >= 0 && leftStickY >= 0) {
      powerLeftGroup = calcPower(leftStickY, leftStickX, powerReduction);
      powerRightGroup = 100 * powerReduction;
        
    } else if (leftStickX <= 0 && leftStickY >= 0) {
      powerRightGroup = calcPower(leftStickY, leftStickX, powerReduction, -1);
      powerLeftGroup = 100 * powerReduction;

    } else if (leftStickX >= 0 && leftStickY <= 0) {
      powerRightGroup = calcPower(leftStickX, leftStickY, powerReduction, -1);
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
    if (leftStickX == 0 && rightStickX == 0) {
      goingStraight = true;
    } else {
      encoderLeftInit = leftEncoder.position(vex::rotationUnits::deg);
      encoderRightInit = rightEncoder.position(vex::rotationUnits::deg);
    }

    printf("right = %f, left = %f\n", powerRightGroup, powerLeftGroup);

    double inputLF = round100(powerRightGroup + rightStickX);
    double inputRR = round100(powerRightGroup - rightStickX);
    double inputLR = round100(powerLeftGroup + rightStickX);
    double inputRF = round100(powerLeftGroup - rightStickX);


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

    vex::motor motors[] = {LeftFront, RightFront, RightRear, LeftRear};
    

    double changedSpeeds[] = {inputLF, inputRF, inputRR, inputLR};
/*
    if (goingStraight) {
      double correctionVal = (leftEncoder.position(vex::rotationUnits::deg) - rightEncoder.position(vex::rotationUnits::deg)) - (encoderLeftInit - encoderRightInit);

      double scaleFactor = 0.01;

      changedSpeeds[0] = inputLF + correctionVal * scaleFactor;
      changedSpeeds[1] = inputRF - correctionVal * scaleFactor;
      changedSpeeds[2] = inputRR - correctionVal * scaleFactor;
      changedSpeeds[3] = inputLR + correctionVal * scaleFactor;



    }*/

    double smoothFactor = 1.5;
    if(leftStickX > 50 || leftStickY > 50) {
      smoothFactor = 0.5;
    }

    for (int i = 0; i < 4; i++) {
      changedSpeeds[i] = (changedSpeeds[i] + (motors[i].velocity(vex::velocityUnits::pct) * smoothFactor)) / (smoothFactor + 1);

      
    }

    spinMotor(LeftFront, changedSpeeds[0]);
    spinMotor(RightFront, changedSpeeds[1]);
    spinMotor(RightRear, changedSpeeds[2]);
    spinMotor(LeftRear, changedSpeeds[3]);

    




  } else {
    LeftFront.stop(vex::brakeType::coast);
    RightFront.stop(vex::brakeType::coast);
    LeftRear.stop(vex::brakeType::coast);
    RightRear.stop(vex::brakeType::coast);
  }

}