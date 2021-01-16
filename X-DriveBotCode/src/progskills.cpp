#include "vex.h"

using namespace vex;

int topSensorInitProg = 0;
int bottomSensorInitProg = 0;

void initializeSensorProg() {
  wait(5000, msec);
  topSensorInitProg = topSensor.value(vex::analogUnits::range12bit);
  bottomSensorInitProg = bottomSensor.value(vex::analogUnits::range12bit);
  while (1) {
    if (topSensor.value(vex::analogUnits::range12bit) > topSensorInitProg) {
      topSensorInitProg = topSensor.value(vex::analogUnits::range12bit) - 70;
    }

    if (bottomSensor.value(vex::analogUnits::range12bit) > bottomSensorInitProg) {
      bottomSensorInitProg = bottomSensor.value(vex::analogUnits::range12bit) - 70;
    }
    //printf("sensorinit = %d\n", topSensorInit);
    wait(100, msec);
  }
}



vex::event startInitTopProg(initializeSensorProg);

double PI = 3.1415926535;

double wheelCirc = 3.25 * PI;

double turnCirc = 16.375 * PI;

void move(double length, double speed, bool waitComp = true) {
  length = length * sqrt(2);
  
  LeftFront.spinFor(length/wheelCirc, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  LeftRear.spinFor(length/wheelCirc, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  RightFront.spinFor(length/wheelCirc, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  RightRear.spinFor(length/wheelCirc, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, waitComp);
}

void spinRobot(double spinAngle, bool spinRight, double speed, bool waitComp = true) {
  double rotations = (turnCirc * (spinAngle / 360.0)) / wheelCirc;

  if (!spinRight) {
    rotations *= -1;
  }

  LeftFront.spinFor(rotations, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  LeftRear.spinFor(rotations, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  RightFront.spinFor(-rotations, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  RightRear.spinFor(-rotations, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, waitComp);

}

void progSkills() {
  startInitTopProg.broadcast();
    
  TopRoller.spinFor(180, vex::rotationUnits::deg, 20, vex::velocityUnits::pct, false);
  RightIntake.spinFor(180, vex::rotationUnits::deg, 20, vex::velocityUnits::pct, false);
  LeftIntake.spinFor(180, vex::rotationUnits::deg, 20, vex::velocityUnits::pct, false);
  
  wait(500, msec);

  LeftIntake.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
  RightIntake.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);

  spinRobot(6, true, 10, true);

  move(17, 20, true);

  LeftIntake.stop(vex::brakeType::coast);
  RightIntake.stop(vex::brakeType::coast);

  spinRobot(8, true, 10, true);

  move(1, 20, true);


  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);

  wait(2000, msec);

  BottomRoller.stop(vex::brakeType::coast);
  TopRoller.stop(vex::brakeType::coast);

  spinRobot(8, false, 10, true);

  move(-3, 10, true);
  move(3, 10, true);
  move(-3, 10, true);
  move(3, 10, true);
  move(-3, 10, true);


  wait(5000, msec);
}