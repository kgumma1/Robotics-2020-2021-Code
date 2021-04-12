#include "vex.h"

using namespace vex;

double wheelCirc = PI * 4;


void intake(){
  LeftIntake.spin(vex::directionType::fwd, 100, velocityUnits::pct);
  RightIntake.spin(vex::directionType::fwd, 100, velocityUnits::pct);
}

void outtake(){
  LeftIntake.spin(vex::directionType::rev, 100, velocityUnits::pct);
  RightIntake.spin(vex::directionType::rev, 100, velocityUnits::pct);
}

void index(){
  TopRoller.spin(vex::directionType::fwd, 100, velocityUnits::pct);
  BottomRoller.spin(vex::directionType::fwd, 100, velocityUnits::pct);
}

void revIndex(){
  TopRoller.spin(vex::directionType::rev, 100, velocityUnits::pct);
  BottomRoller.spin(vex::directionType::rev, 100, velocityUnits::pct);
}

void runBottomRoller(int speed = 100){
  BottomRoller.spin(vex::directionType::fwd, speed, velocityUnits::pct);
}

void shoot(int speed = 100){
  TopRoller.spin(vex::directionType:: fwd, speed, velocityUnits::pct);
}

void brakeMotor(vex::motor motorName){
  motorName.stop(vex::brakeType::coast);
}

void alignRobot(){
  move(20, 30);
}

vex::event align(alignRobot);

void move(double length, int speed, bool waitComp){
//not completed
}