//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "positional_servo.h"

//=====[Declaration of private defines]========================================

#define DUTY_MIN 0.066
#define DUTY_MAX 0.082
#define PERIOD 0.02 
#define TIME_INCREMENT_MS 5500

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

PwmOut posServo(PF_8); 

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of private global variables]============

//Initializes the PWM period and duty min for the positional servo
void positionalServoInit()
{
    posServo.period(PERIOD); 
    posServo.write(DUTY_MIN); 
}

//Updates the positional servo
void positionalServoUpdate()
{
    posServo.write(DUTY_MAX);
    delay( TIME_INCREMENT_MS );
    posServo.write(DUTY_MIN);
    delay( TIME_INCREMENT_MS );
}

//=====[Declarations (prototypes) of private functions]========================