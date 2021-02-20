#include "vex.h"

using namespace vex;

void rollers() {
  // L1 = intake, L2 = outtake, otherwise stop
  // R2 = run intakes + rollers
  if(ct.ButtonL1.pressing()) {
    BottomRoller.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
    TopRoller.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
    TopRoller.setBrake(vex::brakeType::coast);
  } else if (ct.ButtonL2.pressing()) {
    BottomRoller.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
    TopRoller.spin(vex::directionType::rev, 12, vex::voltageUnits::volt);
    TopRoller.setBrake(vex::brakeType::coast);
  } else if (ct.ButtonY.pressing()) {
    TopRoller.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
    TopRoller.setBrake(vex::brakeType::coast);
  } else {
    BottomRoller.stop(vex::brakeType::coast);
    TopRoller.stop();
  }

}