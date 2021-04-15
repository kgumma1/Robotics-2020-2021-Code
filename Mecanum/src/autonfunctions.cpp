#include "vex.h"

using namespace vex;

void intake(int speed){
  LeftIntake.spin(vex::directionType::fwd, speed, velocityUnits::pct);
  RightIntake.spin(vex::directionType::fwd, speed, velocityUnits::pct);
}

void index(int speed){
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

void alignRobot(int time, int speed, bool waitComp) {
  alignTime = time;
  alignSpeed = speed;

  alignTrigger.broadcast();
  if (waitComp) {
    wait(time, msec);
  }
}

bool redball(){
  return 100 > bottomSensor.hue() || 345 < bottomSensor.hue();
}

bool blueball(){
  return 220 >= bottomSensor.hue() && bottomSensor.hue() >= 150;
}

bool checkred = true;

bool checkColor() {
  if(checkred) {
    return redball();
  } else {
    return blueball();
  }
}
