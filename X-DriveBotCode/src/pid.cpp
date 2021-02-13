#include "vex.h"

using namespace vex;

void movePid (double distance, double maxSpeed) {

  double KP = 0.17;
  double KI = 0;
  double KD = 0.5;

  // 0 position = left encoder, 1 position = right encoder
  double errors[2];
  double powers[2];
  double integrals[2];
  double derivatives[2];
  double prevErrors[2];

  distance = (distance / 19.75) * 720;

  prevErrors[0] = (distance / 19.75) * 360;
  prevErrors[1] = (distance / 19.75) * 360;

  leftEncoder.resetRotation();
  rightEncoder.resetRotation();

  errors[0] = distance - leftEncoder.position(vex::rotationUnits::deg);
  errors[1] = distance - rightEncoder.position(vex::rotationUnits::deg);


  while (fabs(errors[0] + errors[1]) > 20) {
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

      if(powers[0] > maxSpeed) {
        powers[0] = maxSpeed;
      }
      if(powers[1] > maxSpeed) {
        powers[1] = maxSpeed;
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