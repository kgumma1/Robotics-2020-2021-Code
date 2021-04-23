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

void strafeReg(int time, int speed){
  RightFront.spin(vex::directionType::fwd, -speed, velocityUnits::pct);
  RightRear.spin(vex::directionType::fwd, speed, velocityUnits::pct);
  LeftRear.spin(vex::directionType::fwd, -speed, velocityUnits::pct);
  LeftFront.spin(vex::directionType::fwd, speed, velocityUnits::pct);
  wait(time, msec);
  brakeMotor(LeftFront);
  brakeMotor(RightFront);
  brakeMotor(LeftRear);
  brakeMotor(RightRear);
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

int redLowBound;
int blueLowBound;
int blueHighBound;




void initSensors() {
  blueLowBound = bottomSensor.hue() * 1.9;
  blueHighBound = 70 + blueLowBound;
  redLowBound = bottomSensor.hue()*0.85;
}

bool redball(){
  return redLowBound > bottomSensor.hue() ||  300 < bottomSensor.hue();
}

bool blueball(){
  return blueLowBound <= bottomSensor.hue() && blueHighBound >= bottomSensor.hue() ;
}

bool checkred = true;

bool checkOpp() {
   if (checkred){
     return blueball(); 
   } else {
     return redball();
   }
  }

bool checkColor() {
  if(checkred) {
    return redball();
  } else {
    return blueball();
  }

  
}
