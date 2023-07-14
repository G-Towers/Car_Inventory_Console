// Main.cpp Car Inventory

#include "Interface.h"
#include "RecordArray.h"
#include "RecordFunctions.h"


int main()
{
    InvStorage carInv;  // Car inventory arrays.
    InvList carList;    // Car inventory linked list.
    ErrMsgs carErr;     // Error messages.
   

    SwitchWelcomeMenu(carInv, carList, carErr);


    return 0;
}




