#include "vex.h"

using namespace vex;

int printTimer=0;

const double PI = 3.14159265;
const double PROPORTIONFACTOR = 200.0 / 90.0;

void spinMotor(vex::motor motorName, double speedPerc) {
  motorName.spin(vex::directionType::fwd, speedPerc, vex::velocityUnits::pct);
}
/*
void brakeMotor(vex::motor motorName, char braketype) {
  if () {
    motorName.setBrake();
  }
}*/

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
  num = 0.1108 * pow(1.061, (num + 15)) - 0.2698;
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

   
  } else if (abs(leftStickX) <= 30 && abs(leftStickY) <= 30) {
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
    LeftFront.stop(vex::brakeType::coast);
    RightFront.stop(vex::brakeType::coast);
    LeftRear.stop(vex::brakeType::coast);
    RightRear.stop(vex::brakeType::coast);

    
    
  } else if(abs(leftStickX) <= 30) {
    /*if (fabs(double(leftStickY) - averageSpeed) < 10) {
      spinRightMotors(100 * powerReduction * (forwardSpeed - 5));
      spinLeftMotors(100 * powerReduction * (forwardSpeed - 5));
    } else {*/

    spinRightMotors(100 * powerReduction * isPos(leftStickY));
    spinLeftMotors(100 * powerReduction * isPos(leftStickY));
    

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


  } else if(abs(leftStickY) <= 30) {
    spinRightMotors(100 * powerReduction * isPos(leftStickX));
    spinLeftMotors(-100 * powerReduction * isPos(leftStickX)); 

  } else if (abs(leftStickX) <= 30 && abs(leftStickY) <= 30) {
      
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

    double reductionAmount = 0;
    double speedLF = getMotorSpeed(LeftFront);
    double speedLR = getMotorSpeed(LeftFront);
    double speedRF = getMotorSpeed(LeftFront);
    double speedRR = getMotorSpeed(LeftFront);


    // if a two motors in a single group spin at different speeds, reduce the speed of
    // the faster one, and spin the other at normal speed
    if (speedLF > speedRR) {
      reductionAmount = (speedLF / speedRR) - 1;
      spinMotor(LeftFront, powerRightGroup * reductionAmount);
      spinMotor(RightRear, powerRightGroup);
    } else {
      reductionAmount = (speedRR / speedLF) - 1;
      spinMotor(LeftFront, powerRightGroup);
      spinMotor(RightRear, powerRightGroup * reductionAmount);
    }

    if (speedLR > speedRF) {
      reductionAmount = (speedLR / speedRF) - 1;
      spinMotor(LeftRear, powerLeftGroup * reductionAmount);
      spinMotor(RightFront, powerLeftGroup);      
    } else {
      reductionAmount = (speedRF / speedLR) - 1;
      spinMotor(LeftRear, powerLeftGroup);
      spinMotor(RightFront, powerLeftGroup * reductionAmount);
    }

    //powerRightGroup = roundNum(powerRightGroup, 0, 10);
    //powerLeftGroup = roundNum(powerLeftGroup, 0, 10);

    //printf("right = %f", powerRightGroup);
    //printf(" left = %f/n", powerLeftGroup);
    /*
    spinRightMotors(powerRightGroup);
    spinLeftMotors(powerLeftGroup);
    */
  }

}