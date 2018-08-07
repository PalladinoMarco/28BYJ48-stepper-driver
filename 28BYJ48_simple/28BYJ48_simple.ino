#include "M28BYJ48.h";

// only for debug, set baudrate at 115200
//#define SERIAL_BAUD_RATE  115200

// define motor direction
#define CW  0
#define CCW 1

// declare step motor (step for revolution, pin1, pin2, pin3, pin4)
M28BYJ48 motor_X(4096,  4,  5,  6,  8);
// declare step motor 2
//M28BYJ48 motor_Y(4096,  9,  10,  11,  12);

void setup() {
  // inizialize serial port
  // Serial.begin(SERIAL_BAUD_RATE);
  delay(500);
  // set rpm
  motor_X.tuning(15);
}

void loop() {
  motor_X.moveSteps(512, CW);
  // stop motor function
  motor_X.motorStop();
  delay(50);
  motor_X.moveSteps(512, CCW);
  motor_X.motorStop();
  delay(50);
}
