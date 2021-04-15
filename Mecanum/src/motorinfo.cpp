#include "vex.h"

using namespace vex;



void motorInfo() {
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(5, 20, "MOTOR TEMPERATURES");
  Brain.Screen.printAt(5, 40, "-------Drive-------");
  Brain.Screen.printAt(5, 60, "LeftFront:      %.0f", LeftFront.temperature(vex::temperatureUnits::celsius));
  Brain.Screen.printAt(5, 80, "LeftRear:       %.0f", LeftRear.temperature(vex::temperatureUnits::celsius));
  Brain.Screen.printAt(5, 100, "RightFront:     %.0f", RightFront.temperature(vex::temperatureUnits::celsius));
  Brain.Screen.printAt(5, 120, "RightRear:      %.0f", RightRear.temperature(vex::temperatureUnits::celsius));
  Brain.Screen.printAt(5, 140, "------Intakes------");
  Brain.Screen.printAt(5, 160, "LeftIntake:     %.0f", LeftIntake.temperature(vex::temperatureUnits::celsius));
  Brain.Screen.printAt(5, 180, "RightIntake:    %.0f", RightIntake.temperature(vex::temperatureUnits::celsius));
  Brain.Screen.printAt(5, 200, "------Indexers-----");
  Brain.Screen.printAt(5, 220, "TopIndexer:     %.0f", TopRoller.temperature(vex::temperatureUnits::celsius));
  Brain.Screen.printAt(5, 240, "BottomIndexer:  %.0f", BottomRoller.temperature(vex::temperatureUnits::celsius));
  
}