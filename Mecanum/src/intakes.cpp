#include "vex.h"

using namespace vex;

void ratchet() {

}

void intake(){
  if (ct.ButtonR1.pressing()) {
    LeftIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    RightIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  } else if (ct.ButtonR2.pressing()) {
    LeftIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    RightIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  } else {
    LeftIntake.stop(vex::brakeType::coast);
    RightIntake.stop(vex::brakeType::coast);
  }
}


