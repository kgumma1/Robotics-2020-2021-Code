#include "vex.h"

using namespace vex;

int timermsec = 0;

void keepTime() {
  while(1) {
    wait(1, msec);
    timermsec++;
    
  }
}

vex::event startTimer(keepTime);

void alignF() {
  move(10, 60);
}

vex::event alignFront(alignF);

void alignRight(){
  LeftFront.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  LeftRear.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  RightFront.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  RightRear.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
}

vex::event alignRightSide(alignRight);

// ball in front of starting position is alliance color
void autonSameColor() {
  release();
  movePid(24.5, 50);
  spinRobot(72, false, 40);
  intake();
  BottomRoller.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);

  movePid(26, 30);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);

  while(!(180 < topSensorNew.hue() && topSensorNew.hue() < 250)) {
    wait(5, msec);
  }

  TopRoller.stop(vex::brakeType::hold);

  move(-10, 50);

}

bool redball(){
  return ((70 > topSensorNew.hue()) && topSensorNew.isNearObject());
}

bool blueball(){
  return ((220 >= topSensorNew.hue() && topSensorNew.hue() >= 190) && topSensorNew.isNearObject());
}

bool checkred = true;
// ball in front of starting position is not alliance color
void autonDifferentColor() {
  release();
  movePid(22, 30);
  movePid(10, 40);
  spinRobot(70, true, 40);
  intake();
  BottomRoller.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);

  movePid(13, 30);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);

  while(!(180 < topSensorNew.hue() && topSensorNew.hue() < 250)) {
    wait(5, msec);
  }

  TopRoller.stop(vex::brakeType::hold);

  move(-10, 50);

}

bool checkColor() {
  if(checkred) {
    return redball();
  } else {
    return blueball();
  }
}


void autonRowBlue(bool red) {
  checkred = red;
  startTimer.broadcast();
  release();

  strafeRight(30, 50);
  intake();
  spinRobot(53, false, 30);

  wait(100, msec);

  movePid(39, 100);

  /*strafeRight(2, true, 40);

  wait(100, msec);*/

  brakeMotor(LeftFront);
  brakeMotor(RightFront);
  brakeMotor(LeftRear); 

  RightRear.spinFor(500, msec, 100, vex::velocityUnits::pct);
  LeftFront.spinFor(250, msec, 100, vex::velocityUnits::pct);

  
  alignFront.broadcast();

  wait(400, msec);

  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  outtake(0);
  wait(100, msec);
  outtake(100);
  wait(300, msec);

  movePid(-1, 50);
  outtake(0);
  brakeMotor(LeftFront);
  brakeMotor(RightFront);
  brakeMotor(LeftRear); 
  brakeMotor(RightRear); 

  LeftRear.spinFor(-475, vex::rotationUnits::deg, -70, vex::velocityUnits::pct);
  alignRightSide.broadcast();
  wait(700, msec);

  /*
  movePid(-6.5, 50);
  strafeRight(7, 50);

  spinRobot(61, false, 50);

  strafeRight(5, 70);


  alignRightSide.broadcast();
  wait(500, msec);
  LeftFront.spinFor(100, msec, -100, vex::velocityUnits::pct);

  movePid(-2, 50);*/
  brakeMotor(BottomRoller);
  brakeMotor(TopRoller);
  movePid(-14, 35);
  alignRightSide.broadcast();
  wait(800, msec);
  spinRobot(12, true, 30);
  wait(100, msec);
  strafeRight(-110, 90);

  wait(100, msec);

  spinRobot(30, false, 60);

  intake();

  
  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  movePid(27, 100);


  alignFront.broadcast();

  wait(500, msec);

  while(bottomSensorNew.objectDistance(vex::distanceUnits::mm) > 40){

  }
  wait(200, msec);
  outtake(100);
  while(!topSensorNew.isNearObject()) {

  }

  wait(250, msec);

  /*while(checkColor()) {
    Brain.Screen.printAt(50, 50, "time = %d\n", timermsec);
    if(timermsec >= 14000) {
      break;
      
    }
  }*/

  outtake(100);

  movePid(-25, 90);

  wait(5000, msec);


}

void autonRowRed() {
 checkred = red;
  startTimer.broadcast();
  release();

  strafeRight(19.5, 50);
  intake();
  spinRobot(43, false, 40);

  wait(100, msec);

  movePid(37, 70);

  brakeMotor(LeftFront);
  brakeMotor(RightFront);
  brakeMotor(LeftRear);  
  wait(200, msec);

  RightRear.spinFor(500, msec, 100, vex::velocityUnits::pct);
  LeftFront.spinFor(250, msec, 100, vex::velocityUnits::pct);

  alignFront.broadcast();

  wait(200, msec);

  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  wait(500, msec);
  outtake(50);
  
  movePid(-6.5, 50);
  strafeRight(7, 50);

  spinRobot(60, false, 50);

  strafeRight(5, 70);


  alignRightSide.broadcast();
  wait(500, msec);
  LeftFront.spinFor(100, msec, -100, vex::velocityUnits::pct);

  movePid(-2, 50);
  brakeMotor(BottomRoller);
  brakeMotor(TopRoller);


  spinRobot(10, true, 30);

  strafeRight(-113, 70);

  wait(100, msec);

  spinRobot(37, false, 40);

  wait(100, msec);

  intake();

  
  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  movePid(24, 70);



  wait(100, msec);

  alignFront.broadcast();

  wait(700, msec);

  while(bottomSensorNew.objectDistance(vex::distanceUnits::mm) > 40) {

  }
  outtake(0);

  while(!topSensorNew.isNearObject()) {

  }

  wait(300, msec);

  



  /*while(checkColor()) {
    Brain.Screen.printAt(50, 50, "time = %d\n", timermsec);
    if(timermsec >= 14000) {
      break;
      
    }
  }*/

  brakeMotor(TopRoller);
  brakeMotor(BottomRoller);
  outtake(100);

  movePid(-20, 50);

  wait(5000, msec);


}

void autonRed() {
  release();

  strafeRight(33, 30);
  intake();
  spinRobot(40, false, 40);

  wait(100, msec);

  movePid(45, 50);
  alignFront.broadcast();
  wait(500, msec);
  spinRobot(10, false, 30);

  alignFront.broadcast();
  wait(300, msec);
  outtake(0);

  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);

  while(!topSensorNew.isNearObject()) {

  }
/*
  wait(300, msec);
  while(!topSensorNew.isNearObject()) {

  }
  wait(300, msec);
  while(!topSensorNew.isNearObject()) {

  }*/
  wait(300, msec);
  outtake(0);
  TopRoller.stop(vex::brakeType::hold);
  BottomRoller.stop(vex::brakeType::hold);


  //movePid(-10, 50);
}

void autonBlue() {
  checkred = red;
  startTimer.broadcast();
  release();

  strafeRight(37, 50);
  intake();
  spinRobot(55, false, 30);

  wait(100, msec);

  movePid(44, 100);

  /*strafeRight(2, true, 40);

  wait(100, msec);*/

  brakeMotor(LeftFront);
  brakeMotor(RightFront);
  brakeMotor(LeftRear); 

  RightRear.spinFor(500, msec, 100, vex::velocityUnits::pct);
  LeftFront.spinFor(250, msec, 100, vex::velocityUnits::pct);

  
  alignFront.broadcast();

  wait(200, msec);

  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  outtake(0);
  wait(100, msec);
  outtake(100);
  wait(300, msec);

  movePid(-1, 50);
  outtake(0);
  brakeMotor(LeftFront);
  brakeMotor(RightFront);
  brakeMotor(LeftRear); 
  brakeMotor(RightRear); 

  LeftRear.spinFor(-475, vex::rotationUnits::deg, -70, vex::velocityUnits::pct);
  alignRightSide.broadcast();
  wait(700, msec);

  /*
  movePid(-6.5, 50);
  strafeRight(7, 50);

  spinRobot(61, false, 50);

  strafeRight(5, 70);


  alignRightSide.broadcast();
  wait(500, msec);
  LeftFront.spinFor(100, msec, -100, vex::velocityUnits::pct);

  movePid(-2, 50);*/
  brakeMotor(BottomRoller);
  brakeMotor(TopRoller);
  movePid(-14, 35);
  alignRightSide.broadcast();
  wait(800, msec);
  spinRobot(10, true, 30);
  wait(100, msec);
  strafeRight(-113, 90);

  wait(100, msec);

  spinRobot(32, false, 40);

  intake();

  

  movePid(26, 90);
  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);

  alignFront.broadcast();

  while(bottomSensorNew.objectDistance(vex::distanceUnits::mm) > 40){

  }
  wait(200, msec);
  outtake(100);
  wait(500, msec);
  wait(250, msec);

  /*while(checkColor()) {
    Brain.Screen.printAt(50, 50, "time = %d\n", timermsec);
    if(timermsec >= 14000) {
      break;
      
    }
  }*/

  outtake(100);

  movePid(-25, 90);

  wait(5000, msec);

}