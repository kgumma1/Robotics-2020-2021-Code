#include "vex.h"

using namespace vex;

void auton() {
  int autonselect = 1;
  
  if (autonselect == 0) {
    homerow();
  }

  if (autonselect == 1) {
    coordinated();
  }
}