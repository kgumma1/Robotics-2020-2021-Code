#include "vex.h"

using namespace vex;

// ball in front of starting position is alliance color
void autonSameColor() {
  release();
  movePid(24.5, 50);
  spinRobot(70, false, 40);
  intake();
  BottomRoller.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);

  movePid(26, 30);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);

  while(!(180 < topSensorNew.hue() && topSensorNew.hue() < 250)) {
    wait(5, msec);
  }

  TopRoller.stop(vex::brakeType::hold);

  move(-10, 50);

}

// ball in front of starting position is not alliance color
void autonDifferentColor() {
  release();
  movePid(32, 30);
  spinRobot(70, true, 40);
  intake();
  BottomRoller.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);

  movePid(10, 30);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);

  while(!(180 < topSensorNew.hue() && topSensorNew.hue() < 250)) {
    wait(5, msec);
  }

  TopRoller.stop(vex::brakeType::hold);

  move(-10, 50);

}