//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "payment.h"
#include "LED_lights.h" 
#include "item_selection.h"
#include "dispenser.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of private global variables]============

bool paymentSuccessState = false;

//=====[Declarations (prototypes) of private functions]========================

static void paymentUnsuccessful();
static void paymentSuccessful();

//=====[Implementations of public functions]===================================

//Initializes the dispenser and the payment subsystem
void paymentInit() {
    paymentSuccessState = false;
    dispenserInit();
}

//Updates/evaluates payment based on code entered and its length
void paymentUpdate(char* code, int codeLength ) {
    if ( codeLength == ID_CODE_LENGTH ) {
        for (int i = 0; i < codeLength; i++) {
            if (!('1' <= code[i] || code[i] <= '9')) {
                paymentUnsuccessful();
                return;
            }
        }
        paymentSuccessful();
    } else {
        paymentUnsuccessful();
    }  
}

//Returns true if payment successful, false otherwise
bool paymentValid() {
    return paymentSuccessState;
}

//=====[Implementations of private functions]==================================
 
//Handles unsuccessful payment and corresponding LEDs
static void paymentUnsuccessful() {
    paymentSuccessState = false;
    
    redLightStateWrite( ON );
    greenLightStateWrite( OFF );
    redLightUpdate();
    greenLightUpdate();
}

//Handles successful payment and corresponding LEDs
static void paymentSuccessful() {
    paymentSuccessState = true;
    greenLightStateWrite( ON );
    redLightStateWrite( OFF );
    redLightUpdate();
    greenLightUpdate();
    dispenserUpdate();
}

