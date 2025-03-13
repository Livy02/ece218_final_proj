//=====[#include guards - begin]===============================================

#ifndef _PAYMENT_H_
#define _PAYMENT_H_

//=====[Declaration of public defines]=========================================

#define ID_CODE_LENGTH   4

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void paymentInit();
void paymentUpdate(char* code, int codeLength );
bool paymentValid();


//=====[#include guards - end]=================================================

#endif // _PAYMENT_H_
