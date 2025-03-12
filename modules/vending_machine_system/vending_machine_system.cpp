//=====[Libraries]=============================================================

#include "arm_book_lib.h"

#include "vending_machine_system.h"

#include "user_interface.h"


//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void vendingMachineInit()
{
    userInterfaceInit();
}

void vendingMachineUpdate()
{
    userInterfaceUpdate();
    delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================
