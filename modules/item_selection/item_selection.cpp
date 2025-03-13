//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "item_selection.h"
#include "LED_lights.h" 

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of private global variables]============

bool itemSuccessState = false;
char itemSelectedCode = '\0';

//=====[Declarations (prototypes) of private functions]========================

static void itemSelectionUnsuccessful();
static void itemSelectionSuccessful();
static void itemUpdateStock();
static bool itemLeftInStock();
static bool itemRightInStock();

//=====[Implementations of public functions]===================================

//Initializes item selection
void itemSelectionInit() {
    itemSuccessState = false;
    LEDLightsInit();
}

//Updates/evaluates item selection based on code entered and its length
void itemSelectionUpdate( char* code, int codeLength ) {
    if ( codeLength >= ITEM_CODE_LENGTH ) {
        if (code[0] == 'A' && ((code[1] == '1') || (code[1] == '2'))) {
            itemSelectedCode = code[1];
            if ( itemAvailable() ) {   
                itemSelectionSuccessful();
                itemUpdateStock();
                itemSuccessState = true;
                
            } else {
                itemSelectionUnsuccessful();
                itemSuccessState = false;
            }
        } else {
            itemSelectionUnsuccessful();
            itemSuccessState = false;
        }
    } else {
        itemSelectionUnsuccessful();
        itemSuccessState = false;
    }
}

//Returns true if item selection successful, false otherwise
bool itemSelectionValid() {
    return itemSuccessState;
}

//Returns the selected item code
char itemSelected() {
    return itemSelectedCode; 
}


//=====[Implementations of private functions]==================================

//Handles unsuccessful item selection and corresponding LEDs
static void itemSelectionUnsuccessful() {
    itemSuccessState = false;
    redLightStateWrite( true );
    greenLightStateWrite( OFF );
    redLightUpdate();
    greenLightUpdate();
}

//Handles successful item selection and corresponding LEDs
static void itemSelectionSuccessful() {
    itemSuccessState = true;
    greenLightStateWrite( ON );
    redLightStateWrite( OFF );
    redLightUpdate();
    greenLightUpdate();
}
