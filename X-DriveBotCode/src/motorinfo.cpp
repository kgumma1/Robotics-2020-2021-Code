#include "vex.h"

using namespace vex;



void motorInfo() {
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(5, 20, "DRIVE MOTOR TEMPERATURES");
  Brain.Screen.printAt(5, 40, "LeftFront:      %.0f", LeftFront.temperature(vex::temperatureUnits::celsius));
  Brain.Screen.printAt(5, 60, "LeftRear:       %.0f", LeftRear.temperature(vex::temperatureUnits::celsius));
  Brain.Screen.printAt(5, 80, "RightFront:     %.0f", RightFront.temperature(vex::temperatureUnits::celsius));
  Brain.Screen.printAt(5, 100, "RightRear:      %.0f", RightRear.temperature(vex::temperatureUnits::celsius));
}