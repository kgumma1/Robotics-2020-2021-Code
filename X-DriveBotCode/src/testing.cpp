#include "vex.h"

using namespace vex;

void testing() {

  leftEncoder.resetRotation();
  while(1) {
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(10, 20, "val = %f\n", leftEncoder.position(vex::rotationUnits::deg));
    wait(10, msec);
  }


}