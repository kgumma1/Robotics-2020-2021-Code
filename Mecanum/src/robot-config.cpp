#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
encoder rightEncoder = encoder(Brain.ThreeWirePort.A);
encoder backEncoder = encoder(Brain.ThreeWirePort.C);
encoder leftEncoder = encoder(Brain.ThreeWirePort.G);
optical bottomSensor = optical(PORT11);
distance topSensor = distance(PORT15);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}