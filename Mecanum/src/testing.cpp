#include "vex.h"

using namespace vex;

 

void testing() {

  movePid(-10, 100);

  intake();

  turnRightPid(85, 100);




  splinePid(53, 58, 100, 42.5);




  alignRobot(300, 30, true);


  splinePid(-40, -39, 100, 33);

  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  turnRightPid(145, 100);

  intake(-100);

  movePid(17, 100);


  strafeRightPid(8, 100);





  
}