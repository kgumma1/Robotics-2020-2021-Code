#include "vex.h"

using namespace vex;

void ratchet() {

}

void intakeDrive(){
  if (ct.ButtonR1.pressing() || ct.ButtonR2.pressing()) {
    LeftIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    RightIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  } else if (ct.ButtonA.pressing()){
    LeftIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    RightIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    //LeftIntake.spin(vex::directionType::rev, 6, vex::voltageUnits::volt);
    //RightIntake.spin(vex::directionType::rev, 8, vex::voltageUnits::volt);
  } else {
    LeftIntake.stop(vex::brakeType::coast);
    RightIntake.stop(vex::brakeType::coast);
  }
}


