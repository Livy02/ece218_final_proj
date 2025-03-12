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
static void paymentStateUpdate(bool state);

//=====[Implementations of public functions]===================================
void paymentInit() {
    paymentSuccessState = false;
    dispenserInit();
}

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

void paymentTransaction() {
    greenLightStateWrite( ON );
    redLightStateWrite( OFF );
    redLightUpdate();
    greenLightUpdate();
    dispenserUpdate();
}

bool paymentValid() {
    return paymentSuccessState;
}

float priceOfItem() {
    if ( itemSelected() == LEFT_CHOICE ) {
        return LEFT_PRICE;
    } else {
        return RIGHT_PRICE;
    }
}


//=====[Implementations of private functions]==================================
static void paymentStateUpdate(bool state) {
    paymentSuccessState = state;
}
 
static void paymentUnsuccessful() {
    paymentSuccessState = false;
    
    redLightStateWrite( ON );
    greenLightStateWrite( OFF );
    redLightUpdate();
    greenLightUpdate();

    
}

static void paymentSuccessful() {
    paymentSuccessState = true;
    paymentTransaction();
    /*
    greenLightStateWrite( ON );
    redLightStateWrite( OFF );
    redLightUpdate();
    greenLightUpdate();
    dispenserUpdate();
    */

}
//=====[Implementations of private functions]==================================

