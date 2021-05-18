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
  wait(300, msec);

  intake(20);

  
  countTopBalls(3);

  splinePid(19, 6.5, 100, 16.5);
 
  alignRobot(300);


  index(70);
  intake(100);

  wait(100, msec);

  intake(65);
  bottomBallCounter(3);
  intake(-100);

  while (topBallCount < 3) {
    wait(1, msec);

  }


  index(-40);
  intake(0);

  wait(100, msec);

  indexOffTask = vex::task(indexOff);

  


  splinePid(-62.5, -61.5, 100, 36);


  brakeMotor(TopRoller);
  brakeMotor(BottomRoller);
  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  
  turnRightPid(102, 100);

  movePid(8, 100);
  alignRobot(300, 50);

  countTopBalls(3);

  
  index(60);

  intake(70);

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

  index(15);




  splinePid(53, 58, 100, 43);


  alignRobot(300, 70, true);
  alignRobot(200, 50, false);
  index(100);
  while (topBallCount < 1) {
    wait(1, msec);
  }

  wait(100, msec);

  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  brakeMotor(TopRoller);
  brakeMotor(BottomRoller);

  splinePid(-40, -39, 100, 33);


  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);

  turnRightPid(146, 100);

  intake(-100);

  movePid(22, 100);


  strafeRightPid(15, 100);
















  

  wait(5000, msec);


}