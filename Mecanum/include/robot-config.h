using namespace vex;

extern brain Brain;

// VEXcode devices
extern encoder rightEncoder;
extern encoder backEncoder;
extern encoder leftEncoder;
extern optical bottomSensor;
extern distance topSensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );