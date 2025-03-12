//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "dispenser.h"
#include "motion_sensor.h"
#include "continuous_servo.h"
#include "positional_servo.h"
#include "item_selection.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool dispenserDetected = OFF;
static bool dispenserDetectedState = OFF;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================
void dispenserInit() {
    motionSensorInit();
    continuousServoInit();
    positionalServoInit();
}

void dispenserUpdate() {
    
    dispenserDetectedState = motionSensorRead();
    if (itemSelected() == '1') {
        continuousLeftServoUpdate();
    } else if (itemSelected() == '2') {
        continuousRightServoUpdate();
    }

    if ( dispenserDetectedState ) {
        positionalServoUpdate();
    }
    
}

bool dispenserStateRead() 
{
    return dispenserDetectedState;
}

bool dispenserRead() 
{
    return dispenserDetected;
}

void dispenserDeactivate() 
{
    dispenserDetected = OFF;
}
//=====[Implementations of private functions]==================================
