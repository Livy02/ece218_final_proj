//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"
#include "vending_machine_system.h"
#include "matrix_keypad.h"
#include "display.h"
#include "item_selection.h"
#include "payment.h"


//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000
#define CODE_NUMBER_OF_KEYS_ITEM 2
#define CODE_NUMBER_OF_KEYS_PAY 4
#define DISPLAY_DELAY_MS  1500
#define DISPENSE_DELAY_MS 3000

//=====[Declaration of private data types]=====================================

char itemChosen[ITEM_LENGTH]; 
char studentID[ID_LENGTH]; 

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

transactionState_t transactionState;

//=====[Declaration and initialization of private global variables]============

static bool itemCodeComplete = false;
static bool payCodeComplete = false;
static int numberOfCodeChars = 0;
static bool waitingForItemSelection = true;
static bool waitingForPay = true;


//=====[Declarations (prototypes) of private functions]========================

static void userInterfaceItemMatrixKeypadUpdate(); 
static void userInterfacePaymentMatrixKeypadUpdate();
static void userInterfaceDisplayInit();
static void userInterfaceDisplayUpdate();
static char* itemChosenDisplay();
static char* paymentDisplay();
static void resetSelection(char* code, int codeLength);

//=====[Implementations of public functions]===================================

//Initializes the matrix keypad, display, and the item selection subsystem
void userInterfaceInit()
{
    matrixKeypadInit( SYSTEM_TIME_INCREMENT_MS );
    userInterfaceDisplayInit();
    itemSelectionInit();
    
}

//Updates the user interface based on the current transaction state
void userInterfaceUpdate()
{
    if ( waitingForItemSelection ) {
        userInterfaceItemMatrixKeypadUpdate();
    } 
    if (waitingForPay) {
        userInterfacePaymentMatrixKeypadUpdate();
    }
    userInterfaceDisplayUpdate();
}

//=====[Implementations of private functions]==================================

//Handles item selection proccess 
static void userInterfaceItemMatrixKeypadUpdate() 
{
    static bool displayMessagePending = false;
    static int messageDisplayTime = 0;
    static bool displayValidMessage = false;
    static int accumulatedTime = 0; 

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

                displayCharPositionWrite(0,1);
                displayStringWrite("Selected Valid");

                displayMessagePending = true;
                messageDisplayTime = DISPLAY_DELAY_MS;
                transactionState = PAYMENT_STATE;
                waitingForItemSelection = false;
                numberOfCodeChars = 0;
                waitingForPay = true; 

            } else {
                incorrectCodeState = ON;
                itemCodeComplete = false;
                numberOfCodeChars = 0;
                waitingForItemSelection = true;

                displayMessagePending = true;
                displayValidMessage = false;
                messageDisplayTime = DISPLAY_DELAY_MS;

                displayCharPositionWrite(12,0); 
                displayStringWrite(itemChosenDisplay()); 

                displayCharPositionWrite(0,1);
                displayStringWrite("Selected Invalid");
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
    }

//Resets the selection by clearing the given code
static void resetSelection(char* code, int codeLength) {
    for (int i = 0; i < codeLength; i++) {
        code[i] = '\0';
    }
}

//Handles the payment process
static void userInterfacePaymentMatrixKeypadUpdate() 
{
    static bool displayMessagePending = false;
    static int messageDisplayTime = 0;
    static bool displayValidMessage = false;
    static int accumulatedTime = 0;

    char keyReleased = matrixKeypadUpdate();

    if( keyReleased != '\0' ) {
        transactionState = PAYMENT_STATE;
        studentID[numberOfCodeChars] = keyReleased;
        numberOfCodeChars++;

        displayCharPositionWrite(12,0);
        displayStringWrite(studentID);

        if ( numberOfCodeChars >= CODE_NUMBER_OF_KEYS_PAY ) {
            paymentUpdate(studentID, numberOfCodeChars);
            if (paymentValid()) {
                payCodeComplete = true;
                incorrectCodeState = OFF;

                displayMessagePending = true;
                displayValidMessage = true;
                accumulatedTime = 0;
                messageDisplayTime = DISPLAY_DELAY_MS; 

                numberOfCodeChars = 0;
                waitingForPay = false;

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
}

//Returns the current item chosen
static char* itemChosenDisplay() {
    return itemChosen; 
}

//Returns the current student ID
static char* paymentDisplay() {
    return studentID;
}

//Initializes the display to show the welcome message
static void userInterfaceDisplayInit()
{
    displayInit();
    transactionState = WELCOME_STATE;
}

//Updates the display based on the current transaction state
static void userInterfaceDisplayUpdate()
{
    static bool dispenseMessagePending = false;
    static int dispenseMessageTime = 0;
    static int accumulatedTime = 0;
    static int accumulatedDisplayTime = 0;
    
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

                        dispenseMessagePending = true;
                        dispenseMessageTime = DISPENSE_DELAY_MS;
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
                
                        resetSelection(itemChosen, ITEM_LENGTH);
                        resetSelection(studentID, ID_LENGTH);

                        userInterfaceDisplayInit();
                        userInterfaceUpdate();

                        transactionState = WELCOME_STATE;
                        
                    }
                }
                break;

            case WELCOME_STATE:
                displayInit();
                displayCharPositionWrite(0,0);
                displayStringWrite("Welcome! Please");
                displayCharPositionWrite(0,1);
                displayStringWrite("Select a Snack");
                break;

        }

    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}
