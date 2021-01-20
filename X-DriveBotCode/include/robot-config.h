using namespace vex;

extern brain Brain;

// VEXcode devices
extern line topSensor;
extern line bottomSensor;
extern encoder leftEncoder;
extern encoder rightEncoder;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );