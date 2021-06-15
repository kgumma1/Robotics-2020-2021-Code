#include "vex.h"

using namespace vex;

vex::task printInfo;

int printinfo() {
  while (1) {
    Brain.Screen.printAt(130, 70, "top = %d");
  }
}

vex::task indexOffTask;



void homerow(bool blueAlliance) {
  checkred = blueAlliance;
  intake();
  wait(500, msec);

  intake(100);

  
  countTopBalls(2);

  splinePid(20, 7, 100, 14);
  if (blueAlliance) {
    alignRobot(600);
  } else {
    alignRobot(200);
  }


  index(100);
  intake(60);

  wait(100, msec);

  intake(70);
  changeIntakeSpeed = 50;
  bottomBallCounter(3);
  intake(-100);

  while (topBallCount < 2) {
    wait(1, msec);

  }


  index(-10);
  intake(0);

  wait(500, msec);

  indexOffTask = vex::task(indexOff);

  

  if (blueAlliance) {
    splinePid(-67, -66, 100, 36);

  } else {
    splinePid(-63.5, -62.5, 100, 36.5);
  }


  brakeMotor(TopRoller);
  brakeMotor(BottomRoller);
  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  if (blueAlliance) {
    turnRightPid(103, 100);
  } else {
    turnRightPid(103, 100);
  }
  if (blueAlliance) {
    movePid(9, 100);

  } else {
    movePid(8, 100);
  }
  alignRobot(600, 50, true);

  countTopBalls(3);

  
  index(70);

  intake(60);
  changeIntakeSpeed = 70;
  bottomBallCounter(2);

  intake(-100);

  while (topBallCount < 2) {
    wait(1, msec);
  }
  wait(300, msec);
  brakeMotor(TopRoller);
  brakeMotor(BottomRoller);

  movePid(-10, 100);

  intake();

  turnRightPid(85, 100);

  countTopBalls(5);

  intakeOne();

  index(20);



  if (blueAlliance) {
    splinePid(54, 59, 100, 39.5);
  } else {
    splinePid(54, 59, 100, 42.5);
  }
  alignRobot(1000, 50, false);

  while (topBallCount < 1) {
    wait(1, msec);
    index(100);
  }

  wait(1000, msec);

  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  brakeMotor(TopRoller);
  brakeMotor(BottomRoller);
/*
  splinePid(-40, -39, 100, 33);


  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);

  turnRightPid(139, 100);

  intake(-100);
  if (blueAlliance) {
    movePid(20, 100);
  } else {
    movePid(22, 100);
  }


  strafeRightPid(17, 100);
















  */

  wait(5000, msec);


}