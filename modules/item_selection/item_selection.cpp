//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "item_selection.h"
#include "LED_lights.h" 
//#include "payment.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of private global variables]============

bool itemSuccessState = false;
char itemSelectedCode = '\0';

int itemLeftStock = 5;
int itemRightStock = 5;

//=====[Declarations (prototypes) of private functions]========================

static void itemSelectionUnsuccessful();
static void itemSelectionSuccessful();
static void itemUpdateStock();
static bool itemLeftInStock();
static bool itemRightInStock();


//=====[Implementations of public functions]===================================
void itemSelectionInit() {
    itemSuccessState = false;
    LEDLightsInit();
}

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
        turnRed();
        itemSelectionUnsuccessful();
        itemSuccessState = false;
    }
}

bool itemSelectionValid() {
    return itemSuccessState;
}

char itemSelected() {
    return itemSelectedCode; 
}


//=====[Implementations of private functions]==================================

static void itemSelectionUnsuccessful() {
    itemSuccessState = false;
    redLightStateWrite( true );
    greenLightStateWrite( OFF );
    redLightUpdate();
    greenLightUpdate();
}



static void itemSelectionSuccessful() {
    itemSuccessState = true;
    greenLightStateWrite( ON );
    redLightStateWrite( OFF );
    redLightUpdate();
    greenLightUpdate();
}

static void itemUpdateStock() {
    if ( itemSelectedCode == LEFT_CHOICE ) {
        itemLeftStock = itemLeftStock - 1;
    } else if ( itemSelectedCode == RIGHT_CHOICE ) {
        itemRightStock = itemRightStock - 1;
    }
}

static bool itemLeftInStock() {
    return ( itemLeftStock >= 1 );
}

static bool itemRightInStock() {
    return ( itemRightStock >= 1 );
}

//move this!!
bool itemAvailable() {
    return (itemSelectedCode == LEFT_CHOICE && itemLeftInStock()) || (itemSelectedCode == RIGHT_CHOICE && itemRightInStock());
}

//=====[Implementations of private functions]==================================

