#include "vex.h"

using namespace vex;

void auton() {
  int autonselect = 8;
  
  if (autonselect == 0) {
    homerow(true);
  }

  if(autonselect == 1) {
    homerow(false);
  }

  if (autonselect == 2) {
    coordinated(true);
  }

  if (autonselect == 3) {
    coordinated(false);
  }

  if(autonselect == 4) {
    LeftIntake.spin(vex::directionType::fwd);
    RightIntake.spin(vex::directionType::fwd);
  }

  if(autonselect == 5) {
    
  }

  if(autonselect == 6) {
    twoGoal(true);
  }
  
  if (autonselect == 7) {
    twoGoal(false);
  }

  if (autonselect == 8) {
    testing();
  }
}