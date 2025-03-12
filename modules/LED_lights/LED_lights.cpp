//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "LED_lights.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============
 
PwmOut overHeadLight[] = {(PB_4), (PA_0), (PD_12)};
DigitalOut redLight(D11); 
DigitalOut greenLight(D12); 

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool overHeadLightState = OFF;
static bool redLightState = OFF;
static bool greenLightState = OFF;
static float brightnessRGBLedRedFactor = 1.0f;   // Set to fully on (1.0f)
static float brightnessRGBLedGreenFactor = 1.0f; // Set to fully on (1.0f)
static float brightnessRGBLedBlueFactor = 1.0f;  // Set to fully on (1.0f)

//=====[Declarations (prototypes) of private functions]========================
static void setDutyCycle( lightSystem_t light, float dutyCycle );
static void setPeriod( lightSystem_t light, float period );

//=====[Implementations of public functions]===================================
void turnRed() {
    redLight = ON;
}

void LEDLightsInit()
{
    overHeadLightInit();
    redLight = OFF;
    redLightStateWrite( OFF );
    greenLightStateWrite( OFF );
    greenLight = OFF;
    redLightUpdate();
    greenLightUpdate();

}

void overHeadLightInit()
{
    // Initialize the RGB light to be on initially
    overHeadLightState = true;
    setPeriod( RGB_LED_RED, 0.01f );
    setPeriod( RGB_LED_GREEN, 0.01f );
    setPeriod( RGB_LED_BLUE, 0.01f );

    setDutyCycle( RGB_LED_RED, 1.0f );
    setDutyCycle( RGB_LED_GREEN, 1.0f );
    setDutyCycle( RGB_LED_BLUE, 1.0f );
}

bool overHeadLightStateRead() {
    return overHeadLightState;
}

bool redLightStateRead() {
    return redLightState;
}

bool greenLightStateRead() {
    return greenLightState;
}

void overHeadLightStateWrite( bool state )
{
    overHeadLightState = state;
}

void redLightStateWrite( bool state )
{
    redLightState = state;
}

void greenLightStateWrite( bool state )
{
    greenLightState = state;
}


void redLightUpdate()
{
    if ( redLightState ) {
        redLight = ON;
        greenLight = OFF;
    } else {
        redLight = OFF;
    }

}

void greenLightUpdate()
{
    //same here? ^^
    if ( greenLightState ) {
        greenLight = ON;
        redLight = OFF;
    } else {
        greenLight = OFF;
    }
}


//=====[Implementations of private functions]==================================

static void setDutyCycle( lightSystem_t light, float dutyCycle )
{
    overHeadLight[light].write(dutyCycle);
}

static void setPeriod( lightSystem_t light, float period )
{
    overHeadLight[light].period(period);
}