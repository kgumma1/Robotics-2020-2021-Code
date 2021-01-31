#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
line topSensor = line(Brain.ThreeWirePort.D);
line bottomSensor = line(Brain.ThreeWirePort.E);
encoder leftEncoder = encoder(Brain.ThreeWirePort.A);
encoder rightEncoder = encoder(Brain.ThreeWirePort.G);
limit middleSensor = limit(Brain.ThreeWirePort.C);
/*vex-vision-config:begin*/
vision Vision11 = vision (PORT11, 50);
/*vex-vision-config:end*/

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}