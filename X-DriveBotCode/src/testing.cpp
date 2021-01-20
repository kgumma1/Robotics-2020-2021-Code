#include "vex.h"

using namespace vex;

void testing() {
  leftEncoder.resetRotation();
  while(1) {
    printf("encoder = %ld\n", rightEncoder.value());
    wait(100, msec);
  }

}