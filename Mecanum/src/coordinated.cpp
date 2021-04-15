#include "vex.h"

using namespace vex;





void coordinated(bool blueAlliance) {
  checkred = blueAlliance;
  intake();
  wait(600, msec);

  movePid(3.25, 70);
  strafeRightPid(4, 50);
  
  turnRightPid(-32, 70);
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
  index(-100);
  intake(-100);

  movePid(-35, 100);



  turnRightPid(-57, 70);

  strafeRightPid(-28, 100);

  index(80);

  intake();

  movePid(12, 100);
  //Brain.Screen.printAt(10, 10, "nalkfdjnlkasjlkfdj");

  alignRobot(400, 30);

  
//  while (!( (70 > bottomSensor.hue() || 345 < bottomSensor.hue()) && bottomSensor.isNearObject() ) ) {

  while (!checkColor()) {
    wait(1, msec);
  }

  intake(-100);
  
  wait(100, msec);


  movePid(-17, 70);


}