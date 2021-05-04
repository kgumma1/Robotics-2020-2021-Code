#include "vex.h"

using namespace vex;


void movePid (double distance, double maxSpeed) {
  // ku = 0.165
  // pu = 811 ms
  double KP = 0.13;
  double KI = 0;
  double KD = 0.9;

  // 0 position = left encoder, 1 position = right encoder
  double errors[2];
  double powers[2];
  double integrals[2];
  double derivatives[2];
  double prevErrors[2];

  distance = (distance / (3.25 * 3.14159265)) * 360;

  prevErrors[0] = distance;
  prevErrors[1] = distance;

  leftEncoder.resetRotation();
  rightEncoder.resetRotation();

  errors[0] = distance - leftEncoder.position(vex::rotationUnits::deg);
  errors[1] = distance - rightEncoder.position(vex::rotationUnits::deg);

  while (fabs(errors[0]) > 20 && fabs(errors[1]) > 20) {
      ///*
      errors[0] = distance - leftEncoder.position(vex::rotationUnits::deg);
      errors[1] = distance - rightEncoder.position(vex::rotationUnits::deg);
      //*/
      // alt
      /*
      errors[0] = distance - (leftEncoder.position(vex::rotationUnits::deg) + rightEncoder.position(vex::rotationUnits::deg)) / 2;
      errors[1] = distance - (leftEncoder.position(vex::rotationUnits::deg) + rightEncoder.position(vex::rotationUnits::deg)) / 2;
      */


      integrals[0] = integrals[0] + errors[0];
      integrals[1] = integrals[1] + errors[1];

      if (distance >= 0) {
        if (errors[0] <= 0) {
          integrals[0] = 0;
        }
      } else {
        if (errors[0] >= 0) {
          integrals[0] = 0;
        }
      }

      if (distance >= 0) {
        if (errors[1] <= 0) {
          integrals[1] = 0;
        }
      } else {
        if (errors[1] >= 0) {
          integrals[1] = 0;
        }
      }

      if (fabs(errors[0]) / fabs(distance) > 0.3) {
        integrals[0] = 0;
      }

      if (fabs(errors[1]) / fabs(distance) > 0.3) {
        integrals[1] = 0;
      }

      derivatives[0] = errors[0] - prevErrors[0];
      derivatives[1] = errors[1] - prevErrors[1];

      prevErrors[0] = errors[0];
      prevErrors[1] = errors[1];

      powers[0] = errors[0] * KP + integrals[0] * KI + derivatives[0] * KD;
      powers[1] = errors[1] * KP + integrals[1] * KI + derivatives[1] * KD;

      if(fabs(powers[0]) > fabs(maxSpeed)) {
        powers[0] = maxSpeed * isPos(powers[0]);
      }
      if(fabs(powers[1]) > fabs(maxSpeed)) {
        powers[1] = maxSpeed * isPos(powers[1]);
      }


      LeftFront.spin(vex::directionType::fwd, powers[0], vex::velocityUnits::pct);
      LeftRear.spin(vex::directionType::fwd, powers[0], vex::velocityUnits::pct);

      RightFront.spin(vex::directionType::fwd, powers[1], vex::velocityUnits::pct);
      RightRear.spin(vex::directionType::fwd, powers[1], vex::velocityUnits::pct);

      
    

      wait(15, msec);

  }


  LeftFront.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  LeftRear.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);

  RightFront.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  RightRear.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);


}



void turnRightPid (double angle, double maxSpeed) {
  // ku = 0.165
  // pu = 811 ms
  double KP = 0.29;
  double KI = 0.005;
  double KD = 0.05;

  // 0 position = left encoder, 1 position = right encoder
  double errors[2];
  double powers[2];
  double integrals[2];
  double derivatives[2];
  double prevErrors[2];

  double distance = angle * 3.4;

  prevErrors[0] = distance;
  prevErrors[1] = -distance;

  leftEncoder.resetRotation();
  rightEncoder.resetRotation();

  errors[0] = distance - leftEncoder.position(vex::rotationUnits::deg);
  errors[1] = -distance - rightEncoder.position(vex::rotationUnits::deg);
   
  while (fabs(errors[0]) > 20 && fabs(errors[1]) > 20) {
      /*
      errors[0] = distance - leftEncoder.position(vex::rotationUnits::deg);
      errors[1] = -distance - rightEncoder.position(vex::rotationUnits::deg);
      */
      // alt
      ///*
      errors[0] = distance - (fabs(leftEncoder.position(vex::rotationUnits::deg)) + fabs(rightEncoder.position(vex::rotationUnits::deg)))*isPos(distance) / 2;
      errors[1] = -distance - (fabs(leftEncoder.position(vex::rotationUnits::deg)) + fabs(rightEncoder.position(vex::rotationUnits::deg)))*isPos(distance) / -2;
      //*/


      integrals[0] = integrals[0] + errors[0];
      integrals[1] = integrals[1] + errors[1];

      if (distance >= 0) {
        if (errors[0] <= 0) {
          integrals[0] = 0;
        }
      } else {
        if (errors[0] >= 0) {
          integrals[0] = 0;
        }
      }

      if (distance >= 0) {
        if (errors[1] <= 0) {
          integrals[1] = 0;
        }
      } else {
        if (errors[1] >= 0) {
          integrals[1] = 0;
        }
      }

      if (fabs(errors[0]) / fabs(distance) > 0.3) {
        integrals[0] = 0;
      }

      if (fabs(errors[1]) / fabs(distance) > 0.3) {
        integrals[1] = 0;
      }

      derivatives[0] = errors[0] - prevErrors[0];
      derivatives[1] = errors[1] - prevErrors[1];

      prevErrors[0] = errors[0];
      prevErrors[1] = errors[1];

      powers[0] = errors[0] * KP + integrals[0] * KI + derivatives[0] * KD;
      powers[1] = errors[1] * KP + integrals[1] * KI + derivatives[1] * KD;

      if(fabs(powers[0]) > fabs(maxSpeed)) {
        powers[0] = maxSpeed * isPos(powers[0]);
      }
      if(fabs(powers[1]) > fabs(maxSpeed)) {
        powers[1] = maxSpeed * isPos(powers[1]);
      }

      LeftFront.spin(vex::directionType::fwd, powers[0], vex::velocityUnits::pct);
      LeftRear.spin(vex::directionType::fwd, powers[0], vex::velocityUnits::pct);

      RightFront.spin(vex::directionType::fwd, powers[1], vex::velocityUnits::pct);
      RightRear.spin(vex::directionType::fwd, powers[1], vex::velocityUnits::pct);

      
    

      wait(15, msec);

  }


  LeftFront.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  LeftRear.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);

  RightFront.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  RightRear.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);


}


void strafeRightPid (double distance, double maxSpeed) {
  // ku = 0.165
  // pu = 811 ms
  double KP = 0.5;
  double KI = 0;
  double KD = 0;

  // 0 position = left encoder, 1 position = right encoder
  double error;
  double power;
  double integral = 0;
  double derivative;
  double prevError;

  distance = (distance / (3.25 * 3.14159265)) * 360;

  prevError = distance;

  backEncoder.resetRotation();
  rightEncoder.resetRotation();
  leftEncoder.resetRotation();

  error = distance - backEncoder.position(vex::rotationUnits::deg);

  while (fabs(error) > 20) {
      ///*
      error = distance - backEncoder.position(vex::rotationUnits::deg);
      //*/
      // alt
      /*
      errors[0] = distance - (leftEncoder.position(vex::rotationUnits::deg) + rightEncoder.position(vex::rotationUnits::deg)) / 2;
      errors[1] = distance - (leftEncoder.position(vex::rotationUnits::deg) + rightEncoder.position(vex::rotationUnits::deg)) / 2;
      */


      integral = integral + error;

      if (distance >= 0) {
        if (error <= 0) {
          integral = 0;
        }
      } else {
        if (error >= 0) {
          integral = 0;
        }
      }


      if (fabs(error) / fabs(distance) > 0.3) {
        integral = 0;
      }

      derivative = error - prevError;
      derivative = error - prevError;

      prevError = error;
      prevError = error;

      power = error * KP + integral * KI + derivative * KD;

      if(fabs(power) > fabs(maxSpeed)) {
        power = maxSpeed * isPos(power);
      }
      double offset = 0;
      double offsetKp = 0.5;
      offset = (rightEncoder.position(vex::rotationUnits::deg) - leftEncoder.position(vex::rotationUnits::deg)) * offsetKp;
      Brain.Screen.clearScreen();
      Brain.Screen.printAt(130, 90, "Offset = %.0f", offset);


      LeftFront.spin(vex::directionType::fwd, power + offset, vex::velocityUnits::pct);
      LeftRear.spin(vex::directionType::fwd, -power + offset, vex::velocityUnits::pct);

      RightFront.spin(vex::directionType::fwd, -power - offset, vex::velocityUnits::pct);
      RightRear.spin(vex::directionType::fwd, power - offset, vex::velocityUnits::pct);

      
    

      wait(15, msec);

  }


  LeftFront.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  LeftRear.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);

  RightFront.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  RightRear.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);


}