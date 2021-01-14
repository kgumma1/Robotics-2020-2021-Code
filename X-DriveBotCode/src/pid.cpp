double setPoint;
double sensorVal;
double kP;

void testPid (int setPoint) {

  double error = setPoint - sensorVal;
  
  while (error != 0) {
    double error = setPoint - sensorVal;
    double power = error * kP;
  }
}