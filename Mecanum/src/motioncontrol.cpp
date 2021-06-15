#include "vex.h"

using namespace vex;

void splineToPoint(int pointX, int pointY, int pointHeading) {
  positionInfo current = getPosition(leftEncoder.position(vex::rotationUnits::deg), rightEncoder.position(vex::rotationUnits::deg), backEncoder.position(vex::rotationUnits::deg));
  
}