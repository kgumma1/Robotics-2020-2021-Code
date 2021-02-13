#include "vex.h"

using namespace vex;

void release() {
  
  TopRoller.spinFor(180, vex::rotationUnits::deg, 20, vex::velocityUnits::pct, false);
  RightIntake.spinFor(180, vex::rotationUnits::deg, 20, vex::velocityUnits::pct, false);
  LeftIntake.spinFor(180, vex::rotationUnits::deg, 20, vex::velocityUnits::pct, true);
  
}

void auton() {
  int autonSelect = 6;
  if(autonSelect == 0) {
    testing();
  }
  if (autonSelect == 1) {
    progSkills();
  }
  if(autonSelect == 2) {
    progSkillsCenter();
  }
  if(autonSelect == 3) {
    progSkillsCenAd();
  }
  if(autonSelect == 4) {
    autonSameColor();
  }
  if(autonSelect == 5) {
    autonDifferentColor();
  }
  if(autonSelect == 6) {
    progSkillsNoPid();
  }
  
}