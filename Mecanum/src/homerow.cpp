#include "vex.h"

using namespace vex;

void intake(int speed = 100){
  LeftIntake.spin(vex::directionType::fwd, speed, velocityUnits::pct);
  RightIntake.spin(vex::directionType::fwd, speed, velocityUnits::pct);
}

void outtake(int speed = 100){
  LeftIntake.spin(vex::directionType::rev, speed, velocityUnits::pct);
  RightIntake.spin(vex::directionType::rev, speed, velocityUnits::pct);
}

void index(int speed = 100){
  TopRoller.spin(vex::directionType::fwd, speed, velocityUnits::pct);
  BottomRoller.spin(vex::directionType::fwd, speed, velocityUnits::pct);
}

void brakeMotor(vex::motor motorName){
  motorName.stop(vex::brakeType::coast);
}


int alignTime = 0;
int alignSpeed = 0;

void align(){
  LeftFront.spin(vex::directionType::fwd, alignSpeed, vex::velocityUnits::pct);
  RightFront.spin(vex::directionType::fwd, alignSpeed, vex::velocityUnits::pct);
  LeftRear.spin(vex::directionType::fwd, alignSpeed, vex::velocityUnits::pct);
  RightRear.spin(vex::directionType::fwd, alignSpeed, vex::velocityUnits::pct);
  wait(alignTime, msec);
  brakeMotor(LeftFront);
  brakeMotor(RightFront);
  brakeMotor(LeftRear);
  brakeMotor(RightRear);
  
}

vex::event alignTrigger(align);

void alignRobot(int time, int speed = 50, bool waitComp = false) {
  alignTime = time;
  alignSpeed = speed;

  alignTrigger.broadcast();
  if (waitComp) {
    wait(time, msec);
  }
}

void homerow() {
  intake();
  wait(600, msec);

  movePid(7.5, 70);
  strafeRightPid(4, 50);
  
  turnRightPid(-32, 70);
  alignRobot(300, 70, true);

  index();

  intake(60);
  // blue: 220 >= bottomSensor.hue() && bottomSensor.hue() >= 190) && bottomSensor.isNearObject()
  // red:
  while (!(70 > bottomSensor.hue() && bottomSensor.isNearObject())) {
    wait(1, msec);
  }



  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);

  wait(100, msec);
  index(-100);

  movePid(-70, 100);


  intake(-100);

  turnRightPid(-53, 70);

  strafeRightPid(-26.5, 100);

  index(70);

  intake(50);

  movePid(21, 100);

  alignRobot(400);

  

  while (!(70 > bottomSensor.hue() && bottomSensor.isNearObject())) {
    wait(1, msec);
  }

  intake(0);

  movePid(-25, 70);

  strafeRightPid(-40, 100);

  turnRightPid(-45, 70);





  wait(5000, msec);



}