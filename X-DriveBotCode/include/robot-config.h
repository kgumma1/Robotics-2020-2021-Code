using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern line topSensor;
extern line bottomSensor;
extern encoder leftEncoder;
extern encoder rightEncoder;
extern limit middleSensor;
extern signature Vision11__SIG_1;
extern signature Vision11__SIG_2;
extern signature Vision11__SIG_3;
extern signature Vision11__SIG_4;
extern signature Vision11__SIG_5;
extern signature Vision11__SIG_6;
extern signature Vision11__SIG_7;
extern vision Vision11;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );