#include "vex.h"

using namespace vex;



void ratchet() {

  // turn motor until it starts struggling, then stop
  
  spinMotor(LeftIntake, -40);
  while(!LeftRatchet.pressing()){
    continue;
  }
  LeftIntake.setBrake(vex::brakeType::hold);
  /*
  spinMotor(RightIntake, -70);
  wait(100, msec);
  while(getMotorSpeed(RightIntake) > -40){
    continue;
  }
  RightIntake.setBrake(vex::brakeType::hold);*/
}

void intake(){
  if (ct.ButtonR1.pressing()) {
    LeftIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    RightIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);

    LeftIntake.setBrake(vex::brakeType::coast);
    RightIntake.setBrake(vex::brakeType::coast);
  } else if (ct.ButtonR2.pressing()){
    ratchet();
    //LeftIntake.spin(vex::directionType::rev, intakespeed, vex::velocityUnits::pct);
    //RightIntake.spin(vex::directionType::rev, intakespeed, vex::velocityUnits::pct);
    //LeftIntake.spin(vex::directionType::rev, 6, vex::voltageUnits::volt);
    //RightIntake.spin(vex::directionType::rev, 8, vex::voltageUnits::volt);
  } else {
    LeftIntake.stop();
    RightIntake.stop();
  }
}


