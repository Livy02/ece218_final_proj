//=====[Libraries]=============================================================

#include "vending_machine_system.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    vendingMachineInit();
    while (true) {
        vendingMachineUpdate();
    }
}