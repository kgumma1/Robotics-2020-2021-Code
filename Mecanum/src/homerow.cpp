#include "vex.h"

using namespace vex;

vex::task printInfo;

int printinfo() {
  while (1) {
    Brain.Screen.printAt(130, 70, "top = %d");
  }
}

void homerow(bool blueAlliance) {
  checkred = blueAlliance;
  intake();
  wait(600, msec);

  intake(20);

  
  countTopBalls(3);

  splinePid(13, 6, 100, 11);

  alignRobot(300);


  index(90);
  intake(100);
  bottomBallCounter(3);
  intake(-100);
  
  while (topBallCount < 3) {
    wait(1, msec);
  }


  index(-20);
  intake(0);
  wait(400, msec);

  LeftIntake.stop(vex::brakeType::hold);
  RightIntake.stop(vex::brakeType::hold);
  index(0);
  

  


  splinePid(-62, -57, 100, 51.5);


  brakeMotor(TopRoller);
  brakeMotor(BottomRoller);
  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  
  turnRightPid(87, 100);


  alignRobot(500, 50, true);

  countTopBalls(3);

  
  index();

  intake();

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

  index(100);




  splinePid(53, 58, 100, 39);


  alignRobot(500, 100, true);


  while (topBallCount < 1) {
    wait(1, msec);
  }


  wait(300, msec);
  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  brakeMotor(TopRoller);
  brakeMotor(BottomRoller);

  splinePid(-40, -39, 100, 33);


  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);

  turnRightPid(145, 100);

  intake(-100);

  movePid(25, 100);


  strafeRightPid(8, 100);
















  

  wait(5000, msec);


}