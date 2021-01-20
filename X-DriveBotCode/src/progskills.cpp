#include "vex.h"

using namespace vex;

/*
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
}*/



//vex::event startInitTopProg(initializeSensorProg);

double wheelCirc = 3.25 * PI;

double turnCirc = 12 * PI;

void move(double length, double speed, bool waitComp) {
  
  LeftFront.spinFor(length / 19.75, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  LeftRear.spinFor(length / 19.75, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  RightFront.spinFor(length / 19.75, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  RightRear.spinFor(length / 19.75, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, waitComp);
}

void spinRobot(double spinAngle, bool spinRight, double speed, bool waitComp) {
  double rotations = (turnCirc * (spinAngle / 360.0)) / wheelCirc;

  if (!spinRight) {
    rotations *= -1;
  }

  LeftFront.spinFor(rotations, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  LeftRear.spinFor(rotations, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  RightFront.spinFor(-rotations, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  RightRear.spinFor(-rotations, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, waitComp);

}

void intake() {
  LeftIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  RightIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
}

void outake(int speed) {
  LeftIntake.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  RightIntake.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
}

void index() {
  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
}

void runBottomRoller() {
  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
}

void shoot() {
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
}

void brakeMotor(vex::motor motorname) {
  motorname.stop(vex::brakeType::coast);
}

void progSkills() {
  //startInitTopProg.broadcast();
  release(); // deploy intakes / hood

  vex::motor motors[] = {LeftFront, LeftRear, RightFront, RightRear};

  // line up with ball, spin to correct curved strafe
  strafeRightPid(12.5);
  spinRobot(20, false, 20);

  // get ready to intake ball, move preload up to make space
  BottomRoller.spinFor(700, msec, 100, vex::velocityUnits::pct);
  intake();

  // move slowly to intake, then go fast to move
  move(15, 35, true);
  straightPid(23);

  // spin to corner goal, stop intaking
  spinRobot(30, false, 50);
  brakeMotor(RightIntake);
  brakeMotor(LeftIntake);

  // move to corner goal
  move(8, 50, true);

  // shoot and move second ball up
  runBottomRoller();
  shoot();

  wait(700, msec);

  // stop before launching second ball, don't intake blues
  brakeMotor(TopRoller);
  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  brakeMotor(BottomRoller);

  wait(200, msec);

  //intake();
  //runBottomRoller();


  /*
  spinMotor(TopRoller, 10);

  while(topSensorInitProg - topSensor.value(vex::analogUnits::range12bit) < 30) {
    wait(10, msec);
  }

  brakeMotor(TopRoller);*/

  move(-15, 50);

  strafeRightPid(20);
  

  wait(5000, msec);
;

}

void progSkillsCenter() {
  //startInitTopProg.broadcast();
    
  release();
  
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