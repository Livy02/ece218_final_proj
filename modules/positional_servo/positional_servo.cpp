#include "mbed.h"
#include "arm_book_lib.h"
#include "positional_servo.h"

#define DUTY_MIN 0.020
#define DUTY_MAX 0.110
#define PERIOD 0.02 
#define TIME_INCREMENT_MS 2000

PwmOut posServo(PF_9); 

void positionalServoInit()
{
    posServo.period(PERIOD); // 20ms period
    posServo.write(DUTY_MIN); // 2.5% duty cycle  
}


void positionalServoUpdate()
{
    posServo.write(DUTY_MAX);
    delay( TIME_INCREMENT_MS );
    posServo.write(DUTY_MIN);
    delay( TIME_INCREMENT_MS );
}