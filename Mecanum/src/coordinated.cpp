#include "vex.h"

using namespace vex;


void coordinated(bool blueAlliance) {
  checkred = blueAlliance;
  intake();
  wait(600, msec);

  movePid(3.25, 70);
  strafeRightPid(-4, 50);
  
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


  wait(100, msec);
  brakeMotor(TopRoller);
  brakeMotor(BottomRoller);

  movePid(-4, 100);

  index(-100);
  intake(-100);

  wait(700, msec);


  turnRightPid(245, 100);

  intake();

  movePid(42, 100);

  strafeRightPid(10, 100);

  index();
  

  alignRobot(400, 20, true);

  LeftFront.stop(vex::brakeType::hold);
  RightFront.stop(vex::brakeType::hold);
  LeftRear.stop(vex::brakeType::hold);
  RightRear.stop(vex::brakeType::hold);


  while (!checkColor()) {
    wait(1, msec);
  }
  wait(300, msec);

  while (!checkColor()) {
    wait(1, msec);
  }

  wait(100, msec);

  movePid(-20, 100);

  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  brakeMotor(TopRoller);
  brakeMotor(BottomRoller);


  wait(5000, msec);





}