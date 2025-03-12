//=====[#include guards - begin]===============================================

#ifndef _ITEM_SELECTION_H_
#define _ITEM_SELECTION_H_

//=====[Declaration of public defines]=========================================

#define ITEM_CODE_LENGTH   2
#define LEFT_CHOICE     '1'
#define RIGHT_CHOICE    '2'

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void itemSelectionInit();
void itemSelectionUpdate( char* code, int codeLength );
bool itemSelectionValid();
char itemSelected();
bool itemAvailable();
//=====[#include guards - end]=================================================

#endif // _ITEM_SELECTION_H_
