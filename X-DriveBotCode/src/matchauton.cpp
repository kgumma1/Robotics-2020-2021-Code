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
  move(20, 60);
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
  movePid(22, 50);
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

  strafeRight(31, 50);
  intake();
  spinRobot(51, false, 30);

  wait(100, msec);

  movePid(40, 100);

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

  movePid(-3, 50);
  outtake(0);
  brakeMotor(LeftFront);
  brakeMotor(RightFront);
  brakeMotor(LeftRear); 
  brakeMotor(RightRear); 

  LeftRear.spinFor(-375, vex::rotationUnits::deg, -70, vex::velocityUnits::pct);
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
  movePid(-10, 37);
 
  
  alignRightSide.broadcast();
  wait(800, msec);
  spinRobot(7, true, 30);
  wait(100, msec);
  strafeRight(-110.5, 90);

  wait(100, msec);

  spinRobot(30, false, 60);

  intake();

  
  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  movePid(23, 100);


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

  //outtake(100);

  //movePid(-25, 90);

  //wait(5000, msec);/


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

  strafeRight(-115, 70);

  wait(100, msec);

  spinRobot(41, false, 40);

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
  startTimer.broadcast();
  release();
  intake();


  spinRobot(14, false, 50);


  BottomRoller.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::fwd, 40, vex::velocityUnits::pct);

  while(!topSensorNew.isNearObject()) {


  }


  brakeMotor(BottomRoller);
  TopRoller.stop(vex::brakeType::hold);

  movePid(10, 100);

  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  
  while(bottomSensorNew.objectDistance(vex::distanceUnits::mm) > 40){

  }

  outtake(0);


  brakeMotor(BottomRoller);


  spinRobot(21, false, 50);


  alignFront.broadcast();

  strafeRight(3.5, 50);

  wait(250, msec);

  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);


  while(!topSensorNew.isNearObject()) {


  }

  wait(700, msec);

  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);


  while(!topSensorNew.isNearObject()) {


  }


  intake();

  while(bottomSensorNew.objectDistance(vex::distanceUnits::mm) > 40){
    if(timermsec > 7500) {
      break;
    }
  }

  outtake(0);

  while(!topSensorNew.isNearObject()) {
    if(timermsec > 7500) {
      break;
    }

  }

  intake();

  while(bottomSensorNew.objectDistance(vex::distanceUnits::mm) > 40){
    if(timermsec > 7500) {
      break;
    }
  }

  outtake(100);

  wait(200, msec);



  TopRoller.stop(vex::brakeType::hold);
  brakeMotor(BottomRoller);
  outtake(100);

  
  movePid(-32, 70);

  spinRobot(10, false, 50);

  movePid(-20.5, 70);

  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);

  while(!topSensorNew.isNearObject()) {

  }

  wait(100, msec);

  spinRobot(63, false, 50);

  alignFront.broadcast();

  wait(500, msec);

  intake();

  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);

  while(bottomSensorNew.objectDistance(vex::distanceUnits::mm) > 40){

  }

  outtake(100);

  while(!topSensorNew.isNearObject()) {


  }

  intake();

  while(bottomSensorNew.objectDistance(vex::distanceUnits::mm) > 40){

  }

  brakeMotor(BottomRoller);
  brakeMotor(TopRoller);

  outtake(100);

  wait(100, msec);

  movePid(-10, 50);










}