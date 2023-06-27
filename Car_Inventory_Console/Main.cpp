// Main.cpp Car Inventory

#include "Interface.h"
#include "RecordArray.h"
#include "RecordFunctions.h"


int main()
{
    InvStorage carInv;  // Car inventory arrays.
    ErrMsgs carErr;     // Error messages.
   
    // Read and validate the inventory of automobiles from the file.
    ReadFile(carInv, carErr);

    // Read everything into a separate array.
    RawReadFile(carInv);

    SwitchWelcomeMenu(carInv, carErr);


    return 0;
}




