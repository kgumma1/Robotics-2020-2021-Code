#include "vex.h"

using namespace vex;


void homerow(bool blueAlliance) {
  checkred = blueAlliance;
  intake();
  wait(600, msec);


  initSensors();


  movePid(3.75, 100);
  strafeRightPid(4, 100);
  
  turnRightPid(-32, 100);
  alignRobot(300, 100, true);

  index();

  intake(60);
  while (!checkColor()) {
    wait(1, msec);
  }



  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);

  wait(100, msec);
  index(-100);
  intake(-100);

  movePid(-35, 100);



  turnRightPid(-57, 100);

  strafeRightPid(-25, 70);

  index();

  intake();

  movePid(14, 100);
  //Brain.Screen.printAt(10, 10, "nalkfdjnlkasjlkfdj");
  alignRobot(500, 60);

  
//  while (!( (70 > bottomSensor.hue() || 345 < bottomSensor.hue()) && bottomSensor.isNearObject() ) ) {

  while (!checkColor()) {
    wait(1, msec);
  }

  intake(-100);
  


  movePid(-17, 100);

  strafeRightPid(-33, 100);

  brakeMotor(TopRoller);
  brakeMotor(BottomRoller);
  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);

  turnRightPid(-47, 100);

  intake();
  index();

  movePid(24, 100);

  alignRobot(300);

  while (!checkColor()) {
    wait(1, msec);
  }



  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);

  wait(70, msec);
  index(-100);
  intake(-100);

  movePid(-20, 100);

  LeftFront.stop(vex::brakeType::hold);
  LeftRear.stop(vex::brakeType::hold);
  RightFront.stop(vex::brakeType::hold);
  RightRear.stop(vex::brakeType::hold);




  wait(5000, msec);



}