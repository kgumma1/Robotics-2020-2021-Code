#include "vex.h"

using namespace vex;

void auton() {
  int autonselect = 2;
  
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
}