// Main.cpp Car Inventory

#include "Interface.h"
#include "RecordArray.h"
#include "RecordFunctions.h"


int main()
{
    int carCount = 0;  // Array size for carRec.
    int rawCount = 0;   // Size for raw array.
    int errCount = 0;    // How many records with errors in file.
    int inputCount = 0; // Array size for inputRec.

    // Error message strings.
    string idErrMsg = "";
    string mdlErrMsg = "";
    string quantErrMsg = "";
    string prcErrMsg = "";

    // Array of error messages.
    string errorMsgs[MAX_ERR_MSG] = { "" };

    // Daclare array objects.
    RecordArray carRec;  // Main record array of valid automobiles (only valid records).
    RecordArray rawCarRec;   // Array for unaltered record file (everthing on record file).
    RecordArray inputRec;  // Temp record array for the input of new records.
    Record* ptrRec[MAX_SIZE] = { nullptr };   // Parallel array of pointers (used for sorting).
    

    // Read and validate the inventory of automobiles from the file.
    ReadFile(carRec, ptrRec, errorMsgs, carCount, errCount, idErrMsg,
        mdlErrMsg, quantErrMsg, prcErrMsg);

    // Read everything into a separate array.
    RawReadFile(rawCarRec, rawCount);

    SwitchWelcomeMenu(carRec, ptrRec, inputRec, rawCarRec, carCount,
        inputCount, rawCount, errorMsgs, errCount, idErrMsg, mdlErrMsg, quantErrMsg,
        prcErrMsg);


    // Pointer array to nullptr.
    for (int i = 0; i < MAX_SIZE; i++)
    {
        ptrRec[i] = nullptr;
    }


    return 0;
}




