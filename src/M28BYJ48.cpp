/*---------------------------------------------------------------------------------------*
 *                                                                                       *
 *  Library name:   (M)otor 28BYJ48 Vs 1                                                 *
 *  Author:         Marco Palladino - marck.palladino@gmail.com                          *
 *  Start date:     04.02.2018 (first beta version)                                      *
 *  Last Update:    11.03.2018                                                           *
 *                                                                                       *
 * This work is licensed under the Creative Commons Attribution-                         *
 * Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).                              *
 * To view a copy of this license,                                                       *
 * visit http://creativecommons.org/licenses/by-sa/4.0/ or send a                        *
 * letter to Creative Commons, 171 Second Street, Suite 300,                             *
 * San Francisco, California, 94105, USA.                                                *
 *                                                                                       *
 *                                                                                       *
 * Step Command IN4 IN3 IN2 IN1                                                          *
 * A  01H   0   0   0   1                                                                *
 * AB 03H   0   0   1   1                                                                *
 * B  02H   0   0   1   0                                                                *
 * BC 06H   0   1   1   0                                                                *
 * C  04H   0   1   0   0                                                                *
 * CD 0CH   1   1   0   0                                                                *
 * D  08H   1   0   0   0                                                                *
 * DA 09H   1   0   0   1                                                                *
 *                                                                                       *
 *                                                                                       *
 *---------------------------------------------------------------------------------------*/
 
#include <Arduino.h>
#include "M28BYJ48.h"

// inizialize driver
M28BYJ48::M28BYJ48(int steps_for_rev, int pin_1, int pin_2,
                                      int pin_3, int pin_4)
{
	//set variables
	this->steps_for_rev = steps_for_rev;
	//this->mDirection = 0;
	this->m_dir = 0;
	
	// set pin
	this->pin_1 = pin_1;
	this->pin_2 = pin_2;
	this->pin_3 = pin_3;
	this->pin_4 = pin_4;
	
	// set pin mode
	pinMode(this->pin_1,OUTPUT);
	pinMode(this->pin_2,OUTPUT);
	pinMode(this->pin_3,OUTPUT);
	pinMode(this->pin_4,OUTPUT);
}
// ULN2003 output logic
void M28BYJ48::logicOut( int IN4,int IN3,int IN2,int IN1)
{
  (IN1==1)?digitalWrite(pin_1,1):digitalWrite(pin_1,0);
  (IN2==1)?digitalWrite(pin_2,1):digitalWrite(pin_2,0);
  (IN3==1)?digitalWrite(pin_3,1):digitalWrite(pin_3,0);
  (IN4==1)?digitalWrite(pin_4,1):digitalWrite(pin_4,0);
}

// 28BYJ48 motor phases
void M28BYJ48::step(int phase)
{
  switch (phase)
    {
       case A:  logicOut(0,0,0,1); break;
       case AB: logicOut(0,0,1,1); break;
       case B:  logicOut(0,0,1,0); break; 
       case BC: logicOut(0,1,1,0); break;
       case C:  logicOut(0,1,0,0); break;
       case CD: logicOut(1,1,0,0); break;
       case D:  logicOut(1,0,0,0); break;
       case DA: logicOut(1,0,0,1); break;
       case MOTOR_OFF: logicOut(0,0,0,0); break; // OFF motor
    }
}
// 28BYJ48 set rpm
void M28BYJ48::tuning (unsigned int rpm)
{
    // calculate the step pulse
	  if (rpm > 0) {this->step_pulse = round(60* 1000L * 1000L / this->steps_for_rev / rpm);}
}

// move motor with steps
void M28BYJ48::moveSteps (unsigned long steps, unsigned int m_dir)
{
   // set counter for steps left
   int steps_left = abs(steps);
   
	 // determin direction
   this->m_dir = m_dir;
	 
	 // loop for call phases case
	 while (steps_left > 0)
	 {
   // set timer
	 unsigned long timer = micros();
   
   // move with the pulse timer
   if (timer - this->last_time >= this->step_pulse)
   {
    
   // reset timer
   this->last_time = timer;
	 if (this->m_dir==1) {this->phase+=1; if (this->phase == this->steps_for_rev){this->phase = 0;}}
   else {if (this->phase == 0) {this->phase = this->steps_for_rev;} this->phase-=1;
   }
   steps_left--; // decrement step left counter
   
   // change phase
	 step(this->phase % 8);
   }
  }
}
// move motor with degree
void M28BYJ48::moveDeg (float deg, unsigned int m_dir)
{
  (deg == 'MOTOR_OFF')?step(MOTOR_OFF):moveSteps(round(deg * this->steps_for_rev / 360), m_dir);
}

void M28BYJ48::motorStop(void) {
  step(MOTOR_OFF);
}

// version() returns the version of the library
int M28BYJ48::version(void)
{
  return 2;
}
