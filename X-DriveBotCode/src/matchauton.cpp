#include "vex.h"

using namespace vex;

// ball in front of starting position is alliance color
void autonSameColor() {
  release();
  movePid(35, 50);
  spinRobot(70, true, 40);
  intake();
  BottomRoller.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
  movePid(25, 50);
  wait(300, msec);
  movePid(-30, 50);

  spinRobot(45, false, 40);

  movePid(10);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);

  while(!(180 < topSensorNew.hue() && topSensorNew.hue() < 250)) {
    wait(5, msec);
  }

  TopRoller.stop(vex::brakeType::hold);

}

// ball in front of starting position is not alliance color
void autonDifferentColor() {
  release();
  movePid(35, 50);
  spinRobot(70, false, 40);
  intake();
  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  movePid(25, 50);
  wait(300, msec);
  movePid(-30, 50);

  spinRobot(45, true, 40);
  
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);

  movePid(10);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);

  while(!(180 < topSensorNew.hue() && topSensorNew.hue() < 250)) {
    wait(5, msec);
  }

  TopRoller.stop(vex::brakeType::hold);
}