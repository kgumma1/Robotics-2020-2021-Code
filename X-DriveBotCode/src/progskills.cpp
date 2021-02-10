#include "vex.h"

using namespace vex;

/*
void initializeSensorProg() {
  wait(5000, msec);
  topSensorInitProg = topSensor.value(vex::analogUnits::range12bit);
  bottomSensorInitProg = bottomSensor.value(vex::analogUnits::range12bit);
  while (1) {
    if (topSensor.value(vex::analogUnits::range12bit) > topSensorInitProg) {
      topSensorInitProg = topSensor.value(vex::analogUnits::range12bit) - 70;
    }

    if (bottomSensor.value(vex::analogUnits::range12bit) > bottomSensorInitProg) {
      bottomSensorInitProg = bottomSensor.value(vex::analogUnits::range12bit) - 70;
    }
    //printf("sensorinit = %d\n", topSensorInit);
    wait(100, msec);
  }
}*/



//vex::event startInitTopProg(initializeSensorProg);


double wheelCirc = 3.25 * PI;

double turnCirc = 12 * PI;

void move(double length, double speed, bool waitComp) {
  
  LeftFront.spinFor(length / 19.75, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  LeftRear.spinFor(length / 19.75, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  RightFront.spinFor(length / 19.75, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  RightRear.spinFor(length / 19.75, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, waitComp);
}

void strafeRight(double length, double speed, bool waitComp = true) {
  
  LeftFront.spinFor(length / 19.75, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  LeftRear.spinFor(-length / 19.75, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  RightFront.spinFor(-length / 19.75, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  RightRear.spinFor(length / 19.75, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, waitComp);
}

void spinRobot(double spinAngle, bool spinRight, double speed, bool waitComp) {
  double rotations = (turnCirc * (spinAngle / 360.0)) / wheelCirc;

  if (!spinRight) {
    rotations *= -1;
  }

  LeftFront.spinFor(rotations, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  LeftRear.spinFor(rotations, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  RightFront.spinFor(-rotations, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, false);
  RightRear.spinFor(-rotations, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, waitComp);

}

void intake() {
  LeftIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  RightIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
}

void outtake(int speed) {
  LeftIntake.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  RightIntake.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
}

void index() {
  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
}

void runBottomRoller() {
  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
}

void shoot() {
  TopRoller.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
}

void brakeMotor(vex::motor motorname) {
  motorname.stop(vex::brakeType::coast);
}

void alignRobot() {
  move(15, 20);
}

vex::event align(alignRobot);

void stopRollers(){
  wait(2000, msec);
  BottomRoller.spinFor(-0.5, vex::rotationUnits::rev);
  brakeMotor(BottomRoller);
}

vex::event stopRollersEvent(stopRollers);

void progSkills() {
  
  int shootTimer = 0;
  leftEncoder.resetRotation();
  rightEncoder.resetRotation();
  topSensorInit = topSensor.value(vex::analogUnits::range12bit);
  bottomSensorInit = bottomSensor.value(vex::analogUnits::range12bit);
  printf("TOPINIT = %ld, BOTTOMINIT = %ld\n", topSensorInit, bottomSensorInit);
  printf("TOP = %ld, BOTTOM = %ld\n", topSensor.value(vex::analogUnits::range12bit), bottomSensor.value(vex::analogUnits::range12bit));

  //startInitTopProg.broadcast();
  release(); // deploy intakes / hood
  wait(300, msec);

  vex::motor motors[] = {LeftFront, LeftRear, RightFront, RightRear};

  // line up with ball, spin to correct curved strafe
  //strafe(12.5, 50);
  //spinRobot(15, false, 20);

  // get ready to intake ball
  intake();

  // move slowly to intake, then go fast to move
  move(15, 35, true);
  move(18, 60, true);

  // spin to corner goal
  spinRobot(75, false, 50);


  // move to corner goal
  move(20, 35, true);
  brakeMotor(RightIntake);
  brakeMotor(LeftIntake);

  // self align
  align.broadcast();
  wait(1500, msec);
  move(0, 0);

  RightRear.spinFor(0.125, vex::rotationUnits::rev, 15, vex::velocityUnits::pct, false);
  LeftRear.spinFor(-0.125, vex::rotationUnits::rev, 20, vex::velocityUnits::pct, true);


  /*
    LeftFront.spin(vex::directionType::fwd, 70, vex::velocityUnits::pct);
  LeftRear.spin(vex::directionType::fwd, 70, vex::velocityUnits::pct);
  RightFront.spin(vex::directionType::fwd, 70, vex::velocityUnits::pct);
  RightRear.spin(vex::directionType::fwd, 70, vex::velocityUnits::pct);
  wait(200, msec);
  while(LeftFront.velocity(vex::velocityUnits::pct) > 20) {
    continue;
  }
  brakeMotor(LeftFront);
  brakeMotor(LeftRear);
  brakeMotor(RightFront);
  brakeMotor(RightRear);*/

  // shoot
  runBottomRoller();
  TopRoller.spin(vex::directionType::fwd, 80, vex::velocityUnits::pct);

  shootTimer = 0;
  printf("currval = %ld\n", topSensor.value(vex::analogUnits::range12bit));
  while (!topSensorNew.isNearObject()) {
    shootTimer++;
    if (shootTimer > 5000) {
      break;
    }
    wait(1, msec);
    printf("currval = %ld\n", topSensor.value(vex::analogUnits::range12bit));
  }

  wait(250, msec);

  
  brakeMotor(TopRoller);
  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  brakeMotor(BottomRoller);


  wait(200, msec);
  TopRoller.stop(vex::brakeType::hold);


  //intake();
  //runBottomRoller();


  /*
  spinMotor(TopRoller, 10);

  while(topSensorInitProg - topSensor.value(vex::analogUnits::range12bit) < 30) {
    wait(10, msec);
  }

  brakeMotor(TopRoller);*/


  // back out from corner goal
  move(-29, 35);
  wait(100, msec);
/*
  while(abs(leftEncoder.value()-abs(rightEncoder)) > 10) {
    LeftFront.spin(vex::directionType::fwd, 10, vex::velocityUnits::pct);
    LeftRear.spin(vex::directionType::fwd, 10, vex::velocityUnits::pct);
    RightFront.spin(vex::directionType::fwd, -10, vex::velocityUnits::pct);
    RightRear.spin(vex::directionType::fwd, -10, vex::velocityUnits::pct);
  }*/
  // spin to align to ball on wall
  spinRobot(55, true, 20);

  brakeMotor(LeftFront);
  brakeMotor(LeftRear);
  brakeMotor(RightFront);
  brakeMotor(RightRear);

  // intake and move to ball on wall
  wait(100, msec);
  intake();
  runBottomRoller();
  TopRoller.stop(vex::brakeType::hold);
  
  move(17, 35);
/*
  RightFront.spinFor(400, msec, 50, vex::velocityUnits::pct);
  LeftRear.spinFor(400, msec, 50, vex::velocityUnits::pct);
  RightRear.spinFor(-100, msec, 50, vex::velocityUnits::pct);
  LeftFront.spinFor(-100, msec, 50, vex::velocityUnits::pct);*/

  wait(500, msec);

  // back out and spin to align with ball right in front of edge goal
  BottomRoller.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
  wait(100, msec);
  move(-8, 35); // to change
  wait(100, msec);

  spinRobot(90, true, 30);

  // move loaded ball up to make space for next
  TopRoller.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);

  while (!topSensorNew.isNearObject()) {

  }
  wait(100, msec);
  TopRoller.stop(vex::brakeType::hold);
  wait(100, msec);
  // move to the next ball
  stopRollersEvent.broadcast();

  move(33, 40);

  wait(300, msec);
  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  spinRobot(90, false, 30);  
  wait(100, msec);
  move(7, 50);
  align.broadcast();
  wait(500, msec);


  TopRoller.spinFor(500, msec, -50, vex::velocityUnits::pct);
  shoot();
  runBottomRoller();

  while(!topSensorNew.isNearObject()){

  }
  brakeMotor(BottomRoller);

  wait(400, msec);

  TopRoller.stop(vex::brakeType::hold);
  
  wait(300, msec);

  TopRoller.spinFor(500, msec, -50, vex::velocityUnits::pct);

  move(-15, 35);

  wait(100, msec);

  strafeRight(39, 40);

  intake();
  runBottomRoller();

  move(19, 40);

  wait(300, msec);

  BottomRoller.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);

  TopRoller.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);

  while (!topSensorNew.isNearObject()) {

  }
  TopRoller.stop(vex::brakeType::hold);
  wait(100, msec);
  stopRollersEvent.broadcast();
  wait(100, msec);

  RightFront.spinFor(400, msec, 50, vex::velocityUnits::pct);
  LeftRear.spinFor(400, msec, 50, vex::velocityUnits::pct);
  RightRear.spinFor(-100, msec, 50, vex::velocityUnits::pct);
  LeftFront.spinFor(-100, msec, 50, vex::velocityUnits::pct);
  
  wait(100, msec);


  move(-29, 30);

  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  brakeMotor(BottomRoller);

  spinRobot(39, true, 30);

  wait(100, msec);

  outtake(30);

  move(44, 50);



  align.broadcast();

  wait(2000, msec);

  shoot();

  while (!topSensorNew.isNearObject()) {

  }

  wait(350, msec);
  TopRoller.stop(vex::brakeType::hold);

  wait(100, msec);

  move(-27, 40);

  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);

  wait(100, msec);

  spinRobot(90, true, 30);

  wait(100, msec);

  strafeRight(41, 100);

  wait(100, msec);

  move(7, 40);

  wait(100, msec);

  align.broadcast();

  wait(900, msec);

  shoot();

  runBottomRoller();

  while (!topSensorNew.isNearObject()) {

  }

  wait(300, msec);

  TopRoller.stop(vex::brakeType::hold);
  BottomRoller.stop(vex::brakeType::hold);

  wait(100, msec);

  move(-7, 40);

  wait(100, msec);

  spinRobot(93, true, 30);

  wait(100, msec);

  intake();

  runBottomRoller();

  move(44, 40);

  wait(500, msec);

  brakeMotor(BottomRoller);
  brakeMotor(RightIntake);
  brakeMotor(LeftIntake);



  spinRobot(45, false, 30);

  wait(100, msec);

  move(15, 40);

  wait(200, msec);

  align.broadcast();

  wait(600, msec);

  shoot();

  runBottomRoller();

  while (!topSensorNew.isNearObject()) {

  }

  wait(300, msec);

  TopRoller.stop(vex::brakeType::hold);
  BottomRoller.stop(vex::brakeType::hold);

  wait(100, msec);

  move(-29, 40);

  wait(100, msec);

  spinRobot(45, true, 30);

   // spin to align to ball on wall

  brakeMotor(LeftFront);
  brakeMotor(LeftRear);
  brakeMotor(RightFront);
  brakeMotor(RightRear);

  // intake and move to ball on wall
  wait(100, msec);
  intake();
  runBottomRoller();
  TopRoller.stop(vex::brakeType::hold);
  
  move(23, 35);

  wait(1000, msec);

  brakeMotor(RightIntake);
  brakeMotor(LeftIntake);

  move(-66, 40);

  wait(100, msec);

  spinRobot(90, true, 30);

  wait(200, msec);

  move(37, 40);

  move(-7, 20);

  move(5, 20);

  align.broadcast();

  wait(600, msec);

  shoot();

  runBottomRoller();

  while (!topSensorNew.isNearObject()) {

  }

  wait(300, msec);

  TopRoller.stop(vex::brakeType::hold);
  BottomRoller.stop(vex::brakeType::hold);

  wait(100, msec);

  // move to the next ball
  /*
  brakeMotor(BottomRoller);
  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);

  wait(100, msec);

  strafeRightPid(46);
  wait(100, msec);
  spinRobot(25, false, 20);
  wait(100, msec);

  move(15, 50);

  runBottomRoller();
  shoot();
  shootTimer = 0;
  printf("currval2 = %ld\n", topSensor.value(vex::analogUnits::range12bit));
  while (topSensor.value(vex::analogUnits::range12bit)  > topSensorInit - 20) {
    shootTimer++;
    if (shootTimer > 5000) {
      break;
    }
    wait(1, msec);
    printf("currval2 = %ld\n", topSensor.value(vex::analogUnits::range12bit));
  }

  brakeMotor(BottomRoller);

  wait(500, msec);

  TopRoller.stop(vex::brakeType::hold);


  move(-13, 50);

  spinRobot(25, true, 30);

  wait(100, msec);

  strafeRightPid(57);

  wait(100, msec);
  //spinRobot(37, true, 50);
  wait(100, msec);

  TopRoller.stop(vex::brakeType::hold);
  /*intake();
  runBottomRoller();

  move(11, 50);

  wait(500, msec);

  brakeMotor(BottomRoller);
  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);

  move(-20, 50);*//*
  //move(-10, 50);

  wait(100, msec);

  //spinRobot(25, true, 50);

  wait(100, msec);
  outtake(100);

  move(33, 50);

  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  wait(100, msec);

  runBottomRoller();
  shoot();
  shootTimer = 0;
  while (topSensor.value(vex::analogUnits::range12bit)  > topSensorInit - 20) {
    shootTimer++;
    if (shootTimer > 5000) {
      break;
    }
    wait(1, msec);
  }

  brakeMotor(BottomRoller);

  wait(500, msec);

  TopRoller.stop(vex::brakeType::hold);

  move(-30, 50);

  wait(100, msec);

  spinRobot(190, true, 40);

  wait(100, msec);

  move(30, 50);

  spinRobot(50, true, 20);

  wait(100, msec);

  move(40, 50);

  wait(2000, msec);*/
;

}

void progSkillsCenter() {
  //startInitTopProg.broadcast();
    
  release();
  
  wait(500, msec);

  LeftIntake.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
  RightIntake.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);

  spinRobot(6, true, 10, true);

  move(17, 20, true);

  LeftIntake.stop(vex::brakeType::coast);
  RightIntake.stop(vex::brakeType::coast);

  spinRobot(8, true, 10, true);

  move(1, 20, true);


  BottomRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);

  wait(2000, msec);

  BottomRoller.stop(vex::brakeType::coast);
  TopRoller.stop(vex::brakeType::coast);

  spinRobot(8, false, 10, true);

  move(-3, 10, true);
  move(3, 10, true);
  move(-3, 10, true);
  move(3, 10, true);
  move(-3, 10, true);


  wait(5000, msec);
}

void progSkillsCenAd() {
  //startInitTopProg.broadcast();
    
  release();
  outtake(100);
  move(70, 20);

  
}