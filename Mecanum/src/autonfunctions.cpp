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

void alignLeft(){
  LeftFront.spin(vex::directionType::fwd, alignSpeed, vex::velocityUnits::pct);
  LeftRear.spin(vex::directionType::fwd, alignSpeed, vex::velocityUnits::pct);
  wait(500, msec);
  RightRear.spin(vex::directionType::fwd, alignSpeed, vex::velocityUnits::pct);
  RightFront.spin(vex::directionType::fwd, alignSpeed, vex::velocityUnits::pct);

  wait(400, msec);
  brakeMotor(LeftFront);
  brakeMotor(RightFront);
  brakeMotor(LeftRear);
  brakeMotor(RightRear);

}

vex::event alignLeftTrigger(alignLeft);

void alignRobotLeft() {

  alignLeftTrigger.broadcast();
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


void bottomBallCounter(int numBallsBottom) {
  int counter = 0;
  bool prevBall = false;
  while (counter < numBallsBottom) {
    if (bottomSensor.isNearObject() && prevBall == false) {
      counter++;
      prevBall = true;

    } else if (!bottomSensor.isNearObject()){
      prevBall = false;
    }

    wait(10, msec);
    //Brain.Screen.clearScreen();
    //Brain.Screen.printAt(130, 90, "b = %d, t = %d", counter, topBallCount);

  }




}

bool nearTopSensor() {
  //return topSensor.objectDistance(vex::distanceUnits::mm) < 80;

  return topSensor.isNearObject();
}



int numBalls;
int topBallCount;

int topBallCounter() {
  topBallCount = 0;
  bool prevBall = false;
  while (topBallCount < numBalls) {
    if (nearTopSensor() && prevBall == false) {
      topBallCount++;
      prevBall = true;

    } else if (!nearTopSensor()){
      prevBall = false;
    }

    wait(1, msec);


    Brain.Screen.setFont(vex::fontType::mono60);

    Brain.Screen.printAt(30, 50, "top = %d", topBallCount);
  }

  wait(150, msec);

  index(-20);
  
  return 0;


}

vex::task topBallTask;

void countTopBalls(int num) {



  topBallTask.stop();
  numBalls = num;
  topBallCount = 0;
  topBallTask = vex::task( topBallCounter );

  
}


int intakeOneStop() {
  while (!bottomSensor.isNearObject()) {
    wait(1, msec);
    intake(60);
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(130, 90, "b = aidflj, t = %d", topBallCount);
  }
  
  Brain.Screen.printAt(130, 90, "t = %d", topBallCount);

  intake(-100);
  index(0);
  return 0;
}

vex::task intakeOffTask;

void intakeOne() {

  intakeOffTask = vex::task( intakeOneStop );
  

}

int indexOff() {

  wait(400, msec);

  LeftIntake.stop(vex::brakeType::hold);
  RightIntake.stop(vex::brakeType::hold);
  index(0);
  return 0;
}
