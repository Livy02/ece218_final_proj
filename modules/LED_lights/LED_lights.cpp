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

//Initializes RGB LED to ON and all other LEDs to OFF
void LEDLightsInit()
{
    overHeadLightInit();
    redLightStateWrite( OFF );
    greenLightStateWrite( OFF );
    redLightUpdate();
    greenLightUpdate();

}

//Initializes the RGB light to be ON initially
void overHeadLightInit()
{
    overHeadLightState = true;
    setPeriod( RGB_LED_RED, 0.01f );
    setPeriod( RGB_LED_GREEN, 0.01f );
    setPeriod( RGB_LED_BLUE, 0.01f );

    setDutyCycle( RGB_LED_RED, 1.0f );
    setDutyCycle( RGB_LED_GREEN, 1.0f );
    setDutyCycle( RGB_LED_BLUE, 1.0f );
}

//Sets the state of the red light
void redLightStateWrite( bool state )
{
    redLightState = state;
}


//Sets the state of the green light
void greenLightStateWrite( bool state )
{
    greenLightState = state;
}

//Updates the red light based on its state
void redLightUpdate()
{
    if ( redLightState ) {
        redLight = ON;
        greenLight = OFF;
    } else {
        redLight = OFF;
    }

}

//Updates the green light based on its state
void greenLightUpdate()
{
    if ( greenLightState ) {
        greenLight = ON;
        redLight = OFF;
    } else {
        greenLight = OFF;
    }
}


//=====[Implementations of private functions]==================================

//Sets the duty cycle for the RGB LED
static void setDutyCycle( lightSystem_t light, float dutyCycle )
{
    overHeadLight[light].write(dutyCycle);
}

//Sets the period for the RGB LED
static void setPeriod( lightSystem_t light, float period )
{
    overHeadLight[light].period(period);
}