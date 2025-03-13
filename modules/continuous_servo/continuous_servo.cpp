//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "continuous_servo.h"

//=====[Declaration of private defines]========================================

#define CONT_SERVO_TIME_INCREMENT_MS 2000
#define DUTY_CYCLE  0.075       
#define PERIOD 0.02     

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

PwmOut contLeftServo(PB_11); 
PwmOut contRightServo(PF_9); 

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

bool leftServoUpdate = false;
bool rightServoUpdate = false;
int accumulatedTime = 0;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

//Initializes the PWM period for left and right servos
void continuousServoInit() {
    contLeftServo.period(PERIOD);
    contRightServo.period(PERIOD);

}

//Updates the left continuous servo
void continuousLeftServoUpdate()
{
    if (!leftServoUpdate) {
        contLeftServo.write(0.065);   
        delay( CONT_SERVO_TIME_INCREMENT_MS );
        leftServoUpdate = true;
        contLeftServo.write(0.075); 
    }
}

//Updates the right continuous servo
void continuousRightServoUpdate()
{ 
    if (!rightServoUpdate) {
        contRightServo.write(0.065);   
        delay( CONT_SERVO_TIME_INCREMENT_MS );
        rightServoUpdate = true;
        contRightServo.write(0.075); 
    }
    
}

//=====[Implementations of private functions]==================================