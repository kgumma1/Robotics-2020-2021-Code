#include "vex.h"

using namespace vex;

void straightPid(double length) {
  double distances[] = {length, length, length, length};
  vex::motor motornames[] = {LeftFront, LeftRear, RightFront, RightRear};
  movePid(distances, motornames, 4);
}

void strafeRightPid(double length) {
  double distances[] = {length, -length, -length, length};
  vex::motor motornames[] = {LeftFront, LeftRear, RightFront, RightRear};
  movePid(distances, motornames, 4);
}

void turnRightPid(double spinAngle) {
  double length = (turnCirc * (spinAngle / 360.0)) / wheelCirc;
  double distances[] = {length, length, -length, -length};
  vex::motor motornames[] = {LeftFront, LeftRear, RightFront, RightRear};
  movePid(distances, motornames, 4);
}

void movePid (double distances[], vex::motor motornames[], int numElements) {

  double KP = 0.1225;
  double KI = 0;
  double KD = 0;
  int stopCounter = 0;

  double errors[numElements];
  double powers[numElements];
  double integrals[numElements];
  double derivatives[numElements];
  double prevErrors[numElements];

  for (int i = 0; i < numElements; i++) {
    motornames[i].resetPosition();
  }

  for (int i = 0; i < numElements; i++) {
    distances[i] = (distances[i] / 19.75) * 900;
  }

  for (int i = 0; i < numElements; i++) {
    prevErrors[i] = motornames[i].position(vex::rotationUnits::raw);
  }

  
  while (1) {
    for (int i = 0; i < numElements; i++) {
      errors[i] = distances[i] - motornames[i].position(vex::rotationUnits::raw);

      integrals[i] = integrals[i] + errors[i];

      if (distances[i] >= 0) {
        if (errors[i] <= 0) {
          integrals[i] = 0;
        }
      } else {
        if (errors[i] >= 0) {
          integrals[i] = 0;
        }
      }

      if (fabs(errors[i]) / fabs(distances[i]) > 0.3) {
        integrals[i] = 0;
      }

      derivatives[i] = errors[i] - prevErrors[i];

      powers[i] = errors[i] * KP + integrals[i] * KI + derivatives[i] * KD;

      motornames[i].spin(vex::directionType::fwd, powers[i], vex::velocityUnits::pct);

      if (motornames[i].velocity(vex::velocityUnits::pct) <= 5 && fabs(errors[i]) / fabs(distances[i]) < 0.2) {
        stopCounter++;
      }
    }

    if(stopCounter == 4) {
      return;
    } else {
      stopCounter = 0;
    }



    wait(15, msec);

  }



}