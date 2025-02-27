#include "mbed.h"
#include "arm_book_lib.h"
#include "continuous_servo.h"


#define TIME_INCREMENT_MS 2000
#define DUTY_CYCLE  0.075        //this is for continuous rotation servo
#define PERIOD 0.0015            //this is for continuous rotation servo


PwmOut contServo(PF_9);

void continuousServoInit() {
    contServo.write(DUTY_CYCLE); 
}

void continuousServoUpdate()
{
    contServo.write(DUTY_CYCLE);    
    delay( TIME_INCREMENT_MS );
}