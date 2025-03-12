//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"


#include "vending_machine_system.h"

#include "matrix_keypad.h"
#include "display.h"
#include "item_selection.h"
#include "payment.h"
#include "continuous_servo.h"
#include "positional_servo.h"

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000
#define CODE_NUMBER_OF_KEYS_ITEM 2
#define CODE_NUMBER_OF_KEYS_PAY 4
#define DISPLAY_DELAY_MS  1500
#define DISPENSE_DELAY_MS 3000
//=====[Declaration of private data types]=====================================
char itemChosen[ITEM_LENGTH]; //change from 10!
char studentID[ID_LENGTH]; //change from 10!
//=====[Declaration and initialization of public global objects]===============

DigitalOut incorrectCodeLed(LED3);
DigitalOut systemBlockedLed(LED2);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

char codeSequenceFromUserInterface[CODE_NUMBER_OF_KEYS_ITEM];
transactionState_t transactionState;

//=====[Declaration and initialization of private global variables]============

static bool incorrectCodeState = OFF;
static bool systemBlockedState = OFF;

static bool itemCodeComplete = false;
static bool payCodeComplete = false;
static int numberOfCodeChars = 0;
static bool waitingForItemSelection = true;
static bool waitingForPay = true;


//=====[Declarations (prototypes) of private functions]========================

//static void userInterfaceMatrixKeypadUpdate();
static void incorrectCodeIndicatorUpdate();
static void systemBlockedIndicatorUpdate();

static void userInterfaceDisplayInit();
static void userInterfaceDisplayUpdate();
static char* itemChosenDisplay();
static char* paymentDisplay();
static void resetSelection(char* code, int codeLength);

//=====[Implementations of public functions]===================================

void userInterfaceInit()
{
    //continuousLeftServoUpdate();
    incorrectCodeLed = OFF;
    systemBlockedLed = OFF;
    matrixKeypadInit( SYSTEM_TIME_INCREMENT_MS );
    userInterfaceDisplayInit();
    itemSelectionInit();
    
}

void userInterfaceUpdate()
{
    if ( waitingForItemSelection ) {
        userInterfaceItemMatrixKeypadUpdate();
    } 
    if (waitingForPay) {
        userInterfacePaymentMatrixKeypadUpdate();
    }
    incorrectCodeIndicatorUpdate();
    systemBlockedIndicatorUpdate();
    userInterfaceDisplayUpdate();
}

bool incorrectCodeStateRead()
{
    return incorrectCodeState;
}

void incorrectCodeStateWrite( bool state )
{
    incorrectCodeState = state;
}

bool systemBlockedStateRead()
{
    return systemBlockedState;
}

void systemBlockedStateWrite( bool state )
{
    systemBlockedState = state;
}

bool userInterfaceCodeCompleteRead()
{
    return itemCodeComplete;
}

void userInterfaceCodeCompleteWrite( bool state )
{
    itemCodeComplete = state;
}

//=====[Implementations of private functions]==================================

void userInterfaceItemMatrixKeypadUpdate() //change this to static
{
    static bool displayMessagePending = false;
    static int messageDisplayTime = 0;
    static bool displayValidMessage = false;
    static int accumulatedTime = 0; 

    static int numberOfHashKeyReleased = 0;
    char keyReleased = matrixKeypadUpdate();

    if( keyReleased != '\0' ) {
        transactionState = ITEM_STATE;
        itemChosen[numberOfCodeChars] = keyReleased;
        numberOfCodeChars++;

        displayCharPositionWrite(12,0);
        displayStringWrite(itemChosen);

        if ( numberOfCodeChars >= CODE_NUMBER_OF_KEYS_ITEM ) {
            itemSelectionUpdate(itemChosen, numberOfCodeChars);

            if (itemSelectionValid() ) {
                itemCodeComplete = true;
                incorrectCodeState = OFF;

                //displayCharPositionWrite(12,0); //
                //displayStringWrite(itemChosenDisplay()); //

                displayCharPositionWrite(0,1);
                displayStringWrite("Selected Valid");

                displayMessagePending = true;
                messageDisplayTime = DISPLAY_DELAY_MS;
                //delay(1500);
                transactionState = PAYMENT_STATE;
                waitingForItemSelection = false;
                numberOfCodeChars = 0;
                waitingForPay = true; ///!!
                //userInterfacePaymentMatrixKeypadUpdate();
            } else {
                incorrectCodeState = ON;
                itemCodeComplete = false;
                numberOfCodeChars = 0;
                waitingForItemSelection = true;

                displayMessagePending = true;
                displayValidMessage = false;
                messageDisplayTime = DISPLAY_DELAY_MS;

                displayCharPositionWrite(12,0); //
                displayStringWrite(itemChosenDisplay()); //

                displayCharPositionWrite(0,1);
                displayStringWrite("Selected Invalid");
                //delay(1500);
            }
            }
        }
        if (displayMessagePending) {
            accumulatedTime += TIME_INCREMENT_MS;

            if (accumulatedTime >= messageDisplayTime) {
                displayMessagePending = false;
                accumulatedTime = 0;
            }
        }
    /*
    static int numberOfHashKeyReleased = 0;
    char keyReleased = matrixKeypadUpdate();

    if( keyReleased != '\0' ) {
        transactionState = ITEM_STATE;
        itemChosen[numberOfCodeChars] = keyReleased;
        numberOfCodeChars++;

        if ( numberOfCodeChars >= CODE_NUMBER_OF_KEYS_ITEM ) {
            itemSelectionUpdate(itemChosen, numberOfCodeChars);
            if (itemSelectionValid() ) {
                itemCodeComplete = true;
                incorrectCodeState = OFF;
                displayCharPositionWrite(0,1);
                displayStringWrite("Selected Valid");
                delay(1500);
                transactionState = PAYMENT_STATE;
                waitingForItemSelection = false;
                numberOfCodeChars = 0;
                waitingForPay = true; ///!!
                //userInterfacePaymentMatrixKeypadUpdate();
            } else {
                incorrectCodeState = ON;
                itemCodeComplete = false;
                numberOfCodeChars = 0;
                waitingForItemSelection = true;
                displayCharPositionWrite(0,1);
                displayStringWrite("Selected Invalid");
                delay(1500);
            }
            }
        }
        */
    }

static void resetSelection(char* code, int codeLength) {
    for (int i = 0; i < codeLength; i++) {
        code[i] = '\0';
    }
}

void userInterfacePaymentMatrixKeypadUpdate() //change this to static
{
    static bool displayMessagePending = false;
    static int messageDisplayTime = 0;
    static bool displayValidMessage = false;
    static int accumulatedTime = 0;

    static int numberOfHashKeyReleased = 0;
    char keyReleased = matrixKeypadUpdate();

    if( keyReleased != '\0' ) {
        transactionState = PAYMENT_STATE;
        studentID[numberOfCodeChars] = keyReleased;
        numberOfCodeChars++;

        displayCharPositionWrite(12,0);
        displayStringWrite(studentID);

        //displayCharPositionWrite(12,0);
        //displayStringWrite("         ");

        if ( numberOfCodeChars >= CODE_NUMBER_OF_KEYS_PAY ) {
            paymentUpdate(studentID, numberOfCodeChars);
            if (paymentValid()) {
                payCodeComplete = true;
                incorrectCodeState = OFF;
                //displayCharPositionWrite(0,1);
                //displayStringWrite("ID Valid");
                //paymentTransaction();

                displayMessagePending = true;
                displayValidMessage = true;
                accumulatedTime = 0;
                messageDisplayTime = DISPLAY_DELAY_MS; 

                //delay(1500);

                numberOfCodeChars = 0;
                waitingForPay = false;
                //transactionState = PAYMENT_STATE;
            } else {
                incorrectCodeState = ON;
                payCodeComplete = false;
                numberOfCodeChars = 0;
                waitingForPay = true;

                displayMessagePending = true;
                displayValidMessage = false;
                accumulatedTime = 0;
                messageDisplayTime = DISPLAY_DELAY_MS;

                displayCharPositionWrite(0,1);
                displayStringWrite("ID Invalid");
    
                //delay(1500);
            }
        }
    }

    if (displayMessagePending) {
        accumulatedTime += TIME_INCREMENT_MS;

        if (accumulatedTime >= messageDisplayTime) {
            displayMessagePending = false;
            accumulatedTime = 0;
        }
    }

    /*
    static int numberOfHashKeyReleased = 0;
    char keyReleased = matrixKeypadUpdate();

    if( keyReleased != '\0' ) {
        transactionState = PAYMENT_STATE;
        studentID[numberOfCodeChars] = keyReleased;
        numberOfCodeChars++;

        //displayCharPositionWrite(12,0);
        //displayStringWrite("         ");

        if ( numberOfCodeChars >= CODE_NUMBER_OF_KEYS_PAY ) {
            paymentUpdate(studentID, numberOfCodeChars);
            if (paymentValid()) {
                payCodeComplete = true;
                incorrectCodeState = OFF;
                displayCharPositionWrite(0,1);
                displayStringWrite("ID Valid");

                delay(1500);
                numberOfCodeChars = 0;
                waitingForPay = false;
                //transactionState = PAYMENT_STATE;
            } else {
                incorrectCodeState = ON;
                payCodeComplete = false;
                numberOfCodeChars = 0;
                waitingForPay = true;
                displayCharPositionWrite(0,1);
                displayStringWrite("ID Invalid");
                delay(1500);
            }
        }
    }
    */
}

static char* itemChosenDisplay() {
    return itemChosen; 
}

static char* paymentDisplay() {
    return studentID;
}

static void userInterfaceDisplayInit()
{
    //displayInit();
    transactionState = WELCOME_STATE;


    //transactionState = ITEM_STATE;
}

static void userInterfaceDisplayUpdate()
{
    static bool dispenseMessagePending = false;
    static int dispenseMessageTime = 0;
    static int accumulatedTime = 0;
    //static bool displayValidMessage = false;

    static int accumulatedDisplayTime = 0;
    //char itemString[10] = "";
    
    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;

        switch( transactionState ) {

            case ITEM_STATE:
                displayInit();
                displayCharPositionWrite(0,0);
                displayStringWrite("Item Chosen:");
                displayCharPositionWrite(12,0);
                displayStringWrite(itemChosenDisplay());
                /*
                if (itemCodeComplete) {
                    if ( !itemSelectionValid() ) {
                        waitingForItemSelection = true;
                        displayCharPositionWrite(0,1);
                        displayStringWrite("Selected Unknown");
                    } else {
                        transactionState = PAYMENT_STATE;
                        waitingForItemSelection = false;
                        displayCharPositionWrite(0,1);
                        displayStringWrite("Enter Student ID:");
                
                displayCharPositionWrite(0,1);
                displayStringWrite("Enter Payment");
                waitingForItemSelection = false;
                */
                
                   // }
               // }
                break;
            case PAYMENT_STATE:
                displayInit();
                displayCharPositionWrite(0,0);
                displayStringWrite("Enter ID #:");
                displayCharPositionWrite(12,0);
                displayStringWrite(paymentDisplay());
                
                if (payCodeComplete) {
                    if (!paymentValid()) {
                        waitingForPay = true;
                   
                        displayCharPositionWrite(0,1);
                        displayStringWrite("ID Unknown");
                    } else {
                        waitingForPay = false;
                        displayCharPositionWrite(0,1);
                        displayStringWrite("Thank you!");
                        //paymentTransaction();

                        dispenseMessagePending = true;
                        dispenseMessageTime = DISPENSE_DELAY_MS;
                        //delay(3000);
                        transactionState = DISPENSE_STATE;
                        
               
                    }
                }
                break;
            case DISPENSE_STATE:
                if (dispenseMessagePending) {
                    accumulatedTime += DISPENSE_DELAY_MS;

                    if (accumulatedTime >= dispenseMessageTime) {
                        dispenseMessagePending = false;
                        accumulatedTime = 0;

                        displayInit();
                        displayCharPositionWrite(0,0);
                        displayStringWrite("Thank you!");

                        //transactionState = WELCOME_STATE;
                
                        resetSelection(itemChosen, ITEM_LENGTH);
                        resetSelection(studentID, ID_LENGTH);

                        userInterfaceDisplayInit();
                        userInterfaceUpdate();

                        transactionState = WELCOME_STATE;
                        
                    }
                }
                break;
            case WELCOME_STATE:
                //waitingForItemSelection = true;
                //waitingForPay = true;
                displayInit();
                displayCharPositionWrite(0,0);
                displayStringWrite("Welcome! Please");
                displayCharPositionWrite(0,1);
                displayStringWrite("Select a Snack");
                break;

        }
        
    /*
        bool ignitionReleased = false;

    switch( ignitionButtonState ) {
        case BUTTON_UP:
            if( ignitionButton ) {
                ignitionButtonState = BUTTON_FALLING;
                accumulatedButtonTime = 0;
            }
            break;

        case BUTTON_FALLING:
            if( accumulatedButtonTime >= TIME_DEBOUNCE_MS ) {
                if( ignitionButton ) {
                    ignitionButtonState = BUTTON_DOWN;
                    ignitionAttempted = true;
                } else {
                    ignitionButtonState = BUTTON_UP;
                }
            }
            accumulatedButtonTime = accumulatedButtonTime + TIME_INCREMENT_MS;
            break;
        
        case BUTTON_DOWN:
            if (!ignitionButton){
                ignitionButtonState = BUTTON_RISING;
                accumulatedButtonTime = 0;
            }
            break;

        case BUTTON_RISING:
            if (!ignitionButton){
                ignitionButtonState = BUTTON_UP;
                ignitionReleased = true;
            }
            else{
                ignitionButtonState = BUTTON_DOWN;
            }
            accumulatedButtonTime = accumulatedButtonTime + TIME_INCREMENT_MS;
            break;
    }
    return ignitionReleased;
    */

        //sprintf(temperatureString, "%.0f", temperatureSensorReadCelsius());
        //displayCharPositionWrite ( 4,0 ); //changed here 4 from 12
        //displayStringWrite( temperatureString );
        //displayCharPositionWrite ( 6,0 ); //changed here 6 from 14
        //char tempWithDegree[] = { (char)223, 'C', '\0' };
        //displayStringWrite(tempWithDegree);

        //displayCharPositionWrite ( 13,0 ); //changed here from 4,1

        //if ( gasDetectorStateRead() ) {
        //    displayStringWrite( "D  " ); //changed here
        //} else {
        //    displayStringWrite( "ND" ); //changed here
        //}

        //displayCharPositionWrite ( 6,1 ); //changed here from 6,2
        
        //if ( sirenStateRead() ) {
        //    displayStringWrite( "ON " );
        //} else {
        //    displayStringWrite( "OFF" );
        //}

    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}

static void incorrectCodeIndicatorUpdate()
{
    incorrectCodeLed = incorrectCodeStateRead();
}

static void systemBlockedIndicatorUpdate()
{
    systemBlockedLed = systemBlockedState;
}