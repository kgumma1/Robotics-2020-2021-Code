#include "vex.h"

using namespace vex;


positionInfo getPosition(int leftEncoderVal, int rightEncoderVal, int backEncoderVal) {

  positionInfo newPosition;
  int positionX = 0;
  int positionY = 0;
  int heading = 0;
  newPosition.x = positionX;
  newPosition.y = positionY;
  newPosition.heading = heading;

  return newPosition;



}