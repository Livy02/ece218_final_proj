//=====[#include guards - begin]===============================================

#ifndef _LED_LIGHTS_H_
#define _LED_LIGHTS_H_

//=====[Declaration of public defines]=========================================
 
//=====[Declaration of public data types]======================================
typedef enum {
    RGB_LED_RED,
    RGB_LED_GREEN,
    RGB_LED_BLUE,
} lightSystem_t;

//=====[Declarations (prototypes) of public functions]=========================

void LEDLightsInit();
void overHeadLightInit();
void redLightStateWrite( bool state );
void greenLightStateWrite( bool state );
void redLightUpdate();
void greenLightUpdate();

//=====[#include guards - end]=================================================

#endif // _LED_LIGHTS_H_