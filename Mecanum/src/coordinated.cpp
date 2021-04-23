#include "vex.h"

using namespace vex;

void alignRight() {
  LeftFront.spin(vex::directionType::fwd, 40, vex::velocityUnits::pct);
  RightFront.spin(vex::directionType::rev, 40, vex::velocityUnits::pct);
  LeftRear.spin(vex::directionType::rev, 40, vex::velocityUnits::pct);
  RightRear.spin(vex::directionType::fwd, 40, vex::velocityUnits::pct);
  wait(1000, msec);
  brakeMotor(LeftFront);
  brakeMotor(RightFront);
  brakeMotor(LeftRear);
  brakeMotor(RightRear);
}

vex::event alignRobotRight(alignRight);

int timeElapsed = 0;

void trackTime() {
  while(1) {
    wait(1, msec);
    timeElapsed++;
  }
}

vex::event startTimer(trackTime);


void coordinated(bool blueAlliance) {
  checkred = blueAlliance;
  startTimer.broadcast();
  
  intake();
  wait(600, msec);

  initSensors();

  movePid(3.25, 70);
  strafeRightPid(-1, 50);
  
  turnRightPid(32, 70);
  alignRobot(300, 70, true);

  index();

  intake(60);
  // blue: 220 >= bottomSensor.hue() && bottomSensor.hue() >= 190) && bottomSensor.isNearObject()
  // red:
  while (!checkColor()) {
    wait(1, msec);
  }



  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  brakeMotor(TopRoller);
  brakeMotor(BottomRoller);

  wait(100, msec);

  index(-100);

  wait(100, msec);
  movePid(-10, 100);
/*
  intake(0);

  wait(700, msec);

  turnRightPid(90, 50);

  intake(-50);
  index(-100);

  wait(400, msec);
  turnRightPid(148, 30);
  intake();

  movePid(40, 70);

  alignRight();


  strafeRightPid(-2, 50);


  index();
  intake();
  

  turnRightPid(17, 30);


  movePid(5.5, 20);


  LeftFront.stop(vex::brakeType::hold);
  RightFront.stop(vex::brakeType::hold);
  LeftRear.stop(vex::brakeType::hold);
  RightRear.stop(vex::brakeType::hold);


  while (!checkOpp()) {
    wait(1, msec);
  }

  wait(300, msec);

  brakeMotor(TopRoller);
  brakeMotor(BottomRoller);

  while(timeElapsed < 14500) {
    wait(1, msec);
  }

  movePid(-20, 100);

  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  brakeMotor(TopRoller);
  brakeMotor(BottomRoller);


  wait(5000, msec);



*/

}