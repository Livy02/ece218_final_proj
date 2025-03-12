//=====[#include guards - begin]===============================================

#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

//=====[Declaration of public defines]=========================================
#define ITEM_LENGTH 2
#define ID_LENGTH 4
#define TIME_INCREMENT_MS 10
//=====[Declaration of public data types]======================================
typedef enum {
    WELCOME_STATE,
    ITEM_STATE,
    PAYMENT_STATE,
    DISPENSE_STATE,
} transactionState_t;
//=====[Declarations (prototypes) of public functions]=========================

void userInterfaceInit();
void userInterfaceUpdate();
bool userInterfaceCodeCompleteRead();
void userInterfaceItemMatrixKeypadUpdate();
void userInterfacePaymentMatrixKeypadUpdate();
void userInterfaceCodeCompleteWrite( bool state );

bool incorrectCodeStateRead();
void incorrectCodeStateWrite( bool state );

bool systemBlockedStateRead();
void systemBlockedStateWrite( bool state );

//=====[#include guards - end]=================================================

#endif // _USER_INTERFACE_H_