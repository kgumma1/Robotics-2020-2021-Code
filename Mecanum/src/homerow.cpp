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

  splinePid(20, 7, 100, 14);
 
  alignRobot(300);


  index(70);
  intake(80);

  wait(100, msec);

  intake(70);
  changeIntakeSpeed = 60;
  bottomBallCounter(3);
  intake(-100);

  while (topBallCount < 3) {
    wait(1, msec);

  }


  index(-10);
  intake(0);

  wait(400, msec);

  indexOffTask = vex::task(indexOff);

  


  splinePid(-64, -63, 100, 36.5);


  brakeMotor(TopRoller);
  brakeMotor(BottomRoller);
  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  
  turnRightPid(101, 100);

  movePid(8, 100);
  alignRobot(600, 50);

  countTopBalls(3);

  
  index(60);

  intake(60);
  changeIntakeSpeed = 60;
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




  splinePid(54, 59, 100, 40.5);

  alignRobot(400, 50, false);
  index(65);
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

  turnRightPid(136, 100);

  intake(-100);

  movePid(23, 100);


  strafeRightPid(17, 100);
















  

  wait(5000, msec);


}