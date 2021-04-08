/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

#include "robot-config.h"

extern brain Brain;
extern competition Competition;


extern vex::motor LeftFront;
extern vex::motor LeftRear;
extern vex::motor RightFront;
extern vex::motor RightRear;

extern vex::motor LeftIntake;
extern vex::motor RightIntake;

extern vex::motor BottomRoller;
extern vex::motor TopRoller;

extern vex::controller ct;

extern const double PI;
extern double turnCirc;
extern double wheelCirc;

extern long bottomSensorInit;
extern long topSensorInit;

void testing();
void motorInfo();

//drive file
void spinMotor(vex::motor motorName, double speedPerc);
double getMotorSpeed(vex::motor motorName);
void drive();

//intakes file
void intakeDrive();

//rollers file
void rollers();

//auton


#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)