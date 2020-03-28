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
 
#ifndef M28BYJ48_h
#define M28BYJ48_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

typedef enum Motor {A, AB, B, BC, C, CD, D, DA, MOTOR_OFF};
typedef enum m_dir {CW, CCW};

// library interface description
class M28BYJ48 {
  public:
    // constructor:
    M28BYJ48(int steps_for_rev, int pin_1, int pin_2,
                                int pin_3, int pin_4);
    
    // mover method:
    void tuning (unsigned int rpm);                                // set rpm
                                                                   // don't set rpm if your add code generate a step pulse and acceleratoon curve (ex grbl)
    void moveSteps (unsigned long steps, m_dir direction);         // move in steps
    void moveDeg (float deg, m_dir direction);                     // move in degree
    void moveMm (float mm, m_dir direction);                       // next upgrade move in mm
    void motorStop (void);                                         // stop motor
    
    int version(void);
    
  private:
    void logicOut( int pin_4,int pin_3,int pin_2,int pin_1);
    void step(Motor phase);
    
    int steps_for_rev;
    m_dir direction;
    unsigned long step_pulse;
    unsigned long last_time;
    Motor phase;
    
    // motor pin numbers:
    int pin_1;
    int pin_2;
    int pin_3;
    int pin_4;
    
};

#endif // M28BYJ48_h
