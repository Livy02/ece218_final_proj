#include "mbed.h"
#include "arm_book_lib.h"
#include "continuous_servo.h"


#define CONT_SERVO_TIME_INCREMENT_MS 2000
#define DUTY_CYCLE  0.075       
#define PERIOD 0.02            


bool leftServoUpdate = false;
bool rightServoUpdate = false;
int accumulatedTime = 0;

PwmOut contLeftServo(PB_11); 
PwmOut contRightServo(PF_9); 
Ticker contTimerClock;

void continuousServoInit() {
    contLeftServo.period(PERIOD);
    contRightServo.period(PERIOD);

}

void continuousLeftServoUpdate()
{
    if (!leftServoUpdate) {
        contLeftServo.write(0.065);   
        delay( CONT_SERVO_TIME_INCREMENT_MS );
        leftServoUpdate = true;
        contLeftServo.write(0.075); 
    }
}

void continuousRightServoUpdate()
{ 
    if (!rightServoUpdate) {
        contRightServo.write(0.065);   
        delay( CONT_SERVO_TIME_INCREMENT_MS );
        rightServoUpdate = true;
        contRightServo.write(0.075); 
    }
    
}