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

void strafeRight(double length, double speed, bool waitComp) {
  
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

void runBottomRoller(int speed = 100) {
  BottomRoller.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
}

void shoot(int speed = 100) {
  TopRoller.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
}

void brakeMotor(vex::motor motorname) {
  motorname.stop(vex::brakeType::coast);
}

void alignRobot() {
  move(20, 30);
}

vex::event align(alignRobot);

void alignBack(){
  move(-20, 20);
}

vex::event alignB(alignBack);

void stopRollers(){
  wait(2000, msec);
  BottomRoller.spinFor(-0.5, vex::rotationUnits::rev);
  brakeMotor(BottomRoller);
}

vex::event stopRollersEvent(stopRollers);

void alignL(){
  strafeRight(-20, 20);
}

vex::event alignLeft(alignL);

void progSkills() {
  //deploy
  release();
  //start intakes for next ball
  intake();
  //move into ball
  movePid(20, 40);
  //spin to first goal
  spinRobot(65, false, 30);
  //stop intakes
  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  //move into goal and align
  move(20, 40);
  align.broadcast();
  wait(1500, msec);
  //run bottom roller and shoot
  runBottomRoller();
  shoot();
  wait(800, msec);
  //back out, spin, and strafe to edge ball
  movePid(-14, 30);/*
  spinRobot(45, true, 30);
  strafeRight(15, 40);
  //intake ball, stop top roller and run bottom at 50%
  intake();
  brakeMotor(TopRoller);
  runBottomRoller(50);
  //move into ball to intake
  movePid(6, 40);
  align.broadcast();
  wait(1000, msec);
  movePid(-8, 40);*//*
  shoot(50);
  brakeMotor(LeftFront);
  brakeMotor(LeftRear);
  brakeMotor(RightFront);
  brakeMotor(RightRear);
  while(!topSensorNew.isNearObject()){

  }
  brakeMotor(TopRoller);
  brakeMotor(BottomRoller);*/
  spinRobot(135, true, 30);
  movePid(-8, 30);
  alignB.broadcast();
  wait(1300, msec);
  //alignLeft.broadcast();
  //wait(500, msec);
  alignB.broadcast();
  wait(1000, msec);
  runBottomRoller(50);
  intake();
  movePid(60, 50);
  //movePid(30, 30);
  runBottomRoller(50);
  while(bottomSensorNew.objectDistance(vex::distanceUnits::mm) > 40){

  }
  brakeMotor(BottomRoller);
}

void trackTime() {
  int time = 0;
  Brain.Screen.setFont(monoXXL);
  while(1) {
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(100, 100, "%i", time);
    wait(1000, msec);
    time+=1;
  }
}

vex::event startTimeTracker(trackTime);

void progSkillsNoPid() {
  startTimeTracker.broadcast();
  
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
  /*
  move(15, 35, true);
  move(18, 60, true);

  // spin to corner goal
  spinRobot(75, false, 50);


  // move to corner goal
  move(20, 35, true);
  brakeMotor(RightIntake);
  brakeMotor(LeftIntake);*/

  strafeRight(13, 35);
  move(39, 50);
  spinRobot(63, false, 45);
  outtake(0);
  move(15, 70);

  // self align
  align.broadcast();
  wait(500, msec);
  move(0, 0);

  RightRear.spinFor(0.175, vex::rotationUnits::rev, 15, vex::velocityUnits::pct, false);
  LeftRear.spinFor(-0.175, vex::rotationUnits::rev, 20, vex::velocityUnits::pct, true);


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
    if (shootTimer > 2000) {
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
  spinRobot(45, true, 20);

  brakeMotor(LeftFront);
  brakeMotor(LeftRear);
  brakeMotor(RightFront);
  brakeMotor(RightRear);

  // intake and move to ball on wall
  wait(100, msec);
  intake();
  runBottomRoller();
  TopRoller.stop(vex::brakeType::hold);
  
  move(21, 45);

 /*
  RightFront.spinFor(400, msec, 50, vex::velocityUnits::pct);
  LeftRear.spinFor(400, msec, 50, vex::velocityUnits::pct);
  RightRear.spinFor(-100, msec, 50, vex::velocityUnits::pct);
  LeftFront.spinFor(-100, msec, 50, vex::velocityUnits::pct);*/

  wait(500, msec);

  // back out and spin to align with ball right in front of edge goal
  BottomRoller.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
  wait(100, msec);
  move(-8, 35); 
  wait(100, msec);

  spinRobot(80, true, 30);

  // move loaded ball up to make space for next
  TopRoller.spin(vex::directionType::fwd, 40, vex::velocityUnits::pct);

  while (!topSensorNew.isNearObject()) {

  }
  wait(100, msec);
  TopRoller.stop(vex::brakeType::hold);
  wait(100, msec);
  // move to the next ball

  

  movePid(36, 70);

  movePid(-2, 30);

  // make sure ball is intaked
  int rollerTimer = 0;
  runBottomRoller(50);
  while(bottomSensorNew.objectDistance(vex::distanceUnits::mm) > 40) {
    rollerTimer++;
    if (rollerTimer > 750) {
      break;
    }

  }

  BottomRoller.spinFor(80, msec, -50, vex::velocityUnits::pct);
  brakeMotor(BottomRoller);
  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);

  // spin and align
  spinRobot(90, false, 30);  
  wait(100, msec);
  move(7.5, 70);
  align.broadcast();
  wait(500, msec);

  // back up ball in indexzer to prepare
  TopRoller.spinFor(500, msec, -20, vex::velocityUnits::pct);
  wait(100, msec);
  shoot();


  // shoot
  shootTimer = 0;
  while(!topSensorNew.isNearObject()){
    shootTimer++;
    if(shootTimer == 500) {
      BottomRoller.spinFor(300, msec, 90, vex::velocityUnits::pct);
    }
    if(shootTimer > 2000) {
      break;
    }
    wait(1, msec);
  }
  brakeMotor(BottomRoller);

  wait(400, msec);

  TopRoller.stop(vex::brakeType::hold);



  // back out and align with strafe to second ball on wall
  move(-15, 35);

  wait(100, msec);

  strafeRight(33, 30);

  BottomRoller.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
  while (!topSensorNew.isNearObject()) {

  }
  TopRoller.stop(vex::brakeType::hold);

  // move forward and intake the ball, move the loaded ball up in slot to make space
  intake();

  move(22, 40);

  BottomRoller.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);

  wait(500, msec);

  outtake(0);

  brakeMotor(BottomRoller);





  wait(100, msec);


  // align with wall
  LeftFront.spinFor(-100, msec, 50, vex::velocityUnits::pct);
  RightRear.spinFor(400, msec, 50, vex::velocityUnits::pct);
  LeftRear.spinFor(-100, msec, 50, vex::velocityUnits::pct);
  RightFront.spinFor(400, msec, 50, vex::velocityUnits::pct);
  
  wait(100, msec);

  // move out and spin to align with goal
  intake();
  movePid(-22, 50);

  wait(500, msec);

  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  brakeMotor(BottomRoller);

  spinRobot(47, true, 30);

  wait(100, msec);

  // move to corner and align, and shoot


  move(44, 50);

  align.broadcast();
  wait(250, msec);
  shoot();

  while (!topSensorNew.isNearObject()) {

  }

  wait(450, msec);
  TopRoller.stop(vex::brakeType::hold);
  brakeMotor(LeftRear);
  brakeMotor(RightFront);
  brakeMotor(LeftFront);
  RightRear.spinFor(1500, msec, -50, vex::velocityUnits::pct);
  LeftFront.spinFor(1000, msec, -50, vex::velocityUnits::pct);
  move(-2, 40);
  wait(100, msec);

  // move out, turn, strafe to next goal

  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);



  strafeRight(64.75, 50);

  wait(100, msec);

  spinRobot(10, false, 30);

  // move into goal, align, shoot
  move(5, 60);

  wait(100, msec);

  align.broadcast();

  wait(2000, msec);

  shoot();

  runBottomRoller();

  while (!topSensorNew.isNearObject()) {

  }

  wait(300, msec);

  TopRoller.stop(vex::brakeType::hold);
  BottomRoller.stop(vex::brakeType::hold);

  wait(100, msec);

  // move out, spin to align with ball on line, go forward and intake
  move(-7.5, 40);

  wait(90, msec);

  spinRobot(83, true, 30);

  wait(100, msec);

  intake();

  runBottomRoller();

  /*move(10, 40);

  wait(100, msec);

  strafeRight(-5, 40);

  wait(100, msec);

  alignLeft.broadcast();

  wait(500, msec);

  strafeRight(5, 40);

  wait(100, msec);

  intake();

  runBottomRoller();

  move(30, 40);*/


  movePid(48, 60);

  wait(500, msec);

  brakeMotor(BottomRoller);
  brakeMotor(RightIntake);
  brakeMotor(LeftIntake);

  // spin to align with goal, move forward, align, score

  spinRobot(56, false, 30);

  wait(100, msec);
  intake();
  wait(500, msec);
  brakeMotor(BottomRoller);
  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);

  wait(100, msec);

  move(18, 60);


  wait(200, msec);

  align.broadcast();

  wait(600, msec);

  shoot();

  runBottomRoller();
  shootTimer = 0;
  while (!topSensorNew.isNearObject()) {
    shootTimer++;
    if(shootTimer > 2000) {
      break;
    }
    wait(1, msec);
  }

  wait(300, msec);

  TopRoller.stop(vex::brakeType::hold);
  BottomRoller.stop(vex::brakeType::hold);

  wait(100, msec);

  // move back, spin and align with wall ball
  move(-35, 40);

  wait(100, msec);

  spinRobot(35, true, 30);


  brakeMotor(LeftFront);
  brakeMotor(LeftRear);
  brakeMotor(RightFront);
  brakeMotor(RightRear);

  // intake and move to ball on wall
  wait(100, msec);
  intake();
  BottomRoller.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
  TopRoller.stop(vex::brakeType::hold);
  
  move(25, 60);

  while(bottomSensorNew.objectDistance(vex::distanceUnits::mm) > 40) {

  }


  spinRobot(10, false, 30);

  wait(1000, msec);



  // move back and spin to align with center goal
  move(-60, 50);

  wait(100, msec);

  brakeMotor(RightIntake);
  brakeMotor(LeftIntake);

  spinRobot(87, true, 30);

  wait(200, msec);

  // move to center goal, descore, shoot, pull out
  move(37, 50);

  move(-9, 25);

  move(9, 100);
  wait(100, msec);

  align.broadcast();

  wait(1500, msec);

  shoot();

  runBottomRoller();

  while (!topSensorNew.isNearObject()) {

  }

  wait(500, msec);

  TopRoller.stop(vex::brakeType::hold);
  BottomRoller.stop(vex::brakeType::hold);

  wait(100, msec);

  move(-15, 100);



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

void progSkillsWithPid() {
  
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


  // get ready to intake ball
  intake();


  strafeRight(13, 35);

  movePid(32, 50);
  spinRobot(65, false, 45);
  outtake(0);
  movePid(10, 40);

  // self align
  align.broadcast();
  wait(500, msec);
  move(0, 0);

  RightRear.spinFor(0.125, vex::rotationUnits::rev, 15, vex::velocityUnits::pct, false);
  LeftRear.spinFor(-0.125, vex::rotationUnits::rev, 20, vex::velocityUnits::pct, true);

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


  // back out from corner goal
  move(-29, 35);
  wait(100, msec);

  // spin to align to ball on wall
  spinRobot(52, true, 20);

  brakeMotor(LeftFront);
  brakeMotor(LeftRear);
  brakeMotor(RightFront);
  brakeMotor(RightRear);

  // intake and move to ball on wall
  wait(100, msec);
  intake();
  runBottomRoller();
  TopRoller.stop(vex::brakeType::hold);

  movePid(11, 60);
/*
  RightFront.spinFor(400, msec, 50, vex::velocityUnits::pct);
  LeftRear.spinFor(400, msec, 50, vex::velocityUnits::pct);
  RightRear.spinFor(-100, msec, 50, vex::velocityUnits::pct);
  LeftFront.spinFor(-100, msec, 50, vex::velocityUnits::pct);*/

  wait(500, msec);

  // back out and spin to align with ball right in front of edge goal
  BottomRoller.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
  wait(100, msec);
  move(-5.5, 35); // to change
  wait(100, msec);

  spinRobot(90, true, 30);

  // move loaded ball up to make space for next
  TopRoller.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);

  while (!topSensorNew.isNearObject()) {

  }
  wait(70, msec);
  TopRoller.stop(vex::brakeType::hold);
  wait(100, msec);
  // move to the next ball

  movePid(30, 60);

  // make sure ball is intaked
  runBottomRoller(50);
  while(bottomSensorNew.objectDistance(vex::distanceUnits::mm) > 40) {

  }

  BottomRoller.spinFor(80, msec, -50, vex::velocityUnits::pct);
  brakeMotor(BottomRoller);
  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);

  // spin and align
  spinRobot(90, false, 30);  
  wait(100, msec);
  move(7.5, 50);
  align.broadcast();
  wait(500, msec);

  // back up ball in indexzer to prepare
  TopRoller.spinFor(600, msec, -20, vex::velocityUnits::pct);
  wait(100, msec);
  shoot();


  // shoot
  while(!topSensorNew.isNearObject()){

  }
  brakeMotor(BottomRoller);

  wait(400, msec);

  TopRoller.stop(vex::brakeType::hold);



  // back out and align with strafe to second ball on wall
  move(-15, 35);

  wait(100, msec);

  strafeRight(37, 30);

  BottomRoller.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
  TopRoller.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
  while (!topSensorNew.isNearObject()) {

  }
  TopRoller.stop(vex::brakeType::hold);

  // move forward and intake the ball, move the loaded ball up in slot to make space
  intake();

  movePid(22, 60);

  BottomRoller.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);

  wait(500, msec);

  outtake(0);

  brakeMotor(BottomRoller);





  wait(100, msec);


  // align with wall
  LeftFront.spinFor(-100, msec, 50, vex::velocityUnits::pct);
  RightRear.spinFor(400, msec, 50, vex::velocityUnits::pct);
  LeftRear.spinFor(-100, msec, 50, vex::velocityUnits::pct);
  RightFront.spinFor(400, msec, 50, vex::velocityUnits::pct);
  
  wait(100, msec);

  // move out and spin to align with goal
  intake();
  move(-24.5, 30);

  wait(500, msec);

  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);
  brakeMotor(BottomRoller);

  spinRobot(40, true, 30);

  wait(100, msec);

  // move to corner and align, and shoot

  movePid(44, 60);

  align.broadcast();
  wait(150, msec);
  shoot();

  while (!topSensorNew.isNearObject()) {

  }

  wait(350, msec);
  TopRoller.stop(vex::brakeType::hold);

  wait(100, msec);

  // move out, turn, strafe to next goal
  move(-27, 40);

  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);

  wait(100, msec);

  spinRobot(52, true, 30);

  wait(100, msec);

  strafeRight(37, 40);

  wait(100, msec);

  // move into goal, align, shoot


  movePid(16, 50);

  wait(100, msec);

  align.broadcast();

  wait(1700, msec);

  shoot();

  runBottomRoller();

  while (!topSensorNew.isNearObject()) {

  }

  wait(300, msec);

  TopRoller.stop(vex::brakeType::hold);
  BottomRoller.stop(vex::brakeType::hold);

  wait(100, msec);

  // move out, spin to align with ball on line, go forward and intake
  move(-7, 40);

  wait(90, msec);

  spinRobot(94, true, 30);

  wait(100, msec);

  intake();

  runBottomRoller();

  movePid(53, 60);

  wait(500, msec);

  brakeMotor(BottomRoller);
  brakeMotor(RightIntake);
  brakeMotor(LeftIntake);

  // spin to align with goal, move forward, align, score

  spinRobot(52, false, 30);

  wait(100, msec);
  intake();
  wait(500, msec);
  brakeMotor(BottomRoller);
  brakeMotor(LeftIntake);
  brakeMotor(RightIntake);

  wait(100, msec);


  movePid(15, 50);


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

  // move back, spin and align with wall ball
  move(-35, 40);

  wait(100, msec);

  spinRobot(35, true, 30);


  brakeMotor(LeftFront);
  brakeMotor(LeftRear);
  brakeMotor(RightFront);
  brakeMotor(RightRear);

  // intake and move to ball on wall
  wait(100, msec);
  intake();
  BottomRoller.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
  TopRoller.stop(vex::brakeType::hold);
  
  movePid(23, 50);

  spinRobot(10, false, 30);

  wait(1000, msec);



  // move back and spin to align with center goal
  move(-66, 50);

  wait(100, msec);

  brakeMotor(RightIntake);
  brakeMotor(LeftIntake);

  spinRobot(90, true, 30);

  wait(200, msec);

  // move to center goal, descore, shoot, pull out

  movePid(37, 50);

  move(-9, 25);

  move(9, 100);
  wait(100, msec);

  align.broadcast();

  wait(1000, msec);

  shoot();

  runBottomRoller();

  while (!topSensorNew.isNearObject()) {

  }

  wait(500, msec);

  TopRoller.stop(vex::brakeType::hold);
  BottomRoller.stop(vex::brakeType::hold);

  wait(100, msec);

  move(-15, 50);

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