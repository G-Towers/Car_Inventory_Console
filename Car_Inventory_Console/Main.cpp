// Main.cpp Car Inventory

#include "RecordArray.h"
#include "RecordFunctions.h"


int main()
{
    int count = 0;  // Array size for carRec.
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
    RecordArray carRec;  // Main record array of automobiles allocated dynamically.
    RecordArray rawCarRec;   // Array for unaltered record file.
    RecordArray inputRec;  // Temp record array for new records.
    Record* ptrRec[MAX_SIZE] = { nullptr };   // Parallel array of pointers.
    

    // Read and validate the inventory of automobiles from the file.
    ReadFile(carRec, ptrRec, errorMsgs, count, errCount, idErrMsg,
        mdlErrMsg, quantErrMsg, prcErrMsg);

    // Read everything into a separate array.
    RawReadFile(rawCarRec, rawCount);

    MainChoice mainMenu = MainChoice::PRINT_ALL;  // Menu enum

    do
    {
        DisplayMainMenu();  // Display the main menu.
        int userInput = MenuUserInput();    // user input.
        mainMenu = (MainChoice)userInput; // cast to enum type.

        switch (mainMenu)
        {
        case MainChoice::PRINT_ALL:
             //ReadFile(carRec, ptrRec, errorMsgs, count, errCount, idErrMsg,
             //       mdlErrMsg, quantErrMsg, prcErrMsg);
            PrintAll(carRec, count);
            break;
        case MainChoice::PRINT_INVALID:
            PrintInvalid(errCount);
            break;
        case MainChoice::SEARCH:
            Search(carRec, count);
            break;
        case MainChoice::SORT:
            SortWrpr(ptrRec, count);
            break;
        case MainChoice::MANAGE_ITEM:
            ManageItem(carRec, ptrRec, inputRec, rawCarRec, errorMsgs, count, inputCount,
                        rawCount, errCount, idErrMsg, mdlErrMsg, quantErrMsg, prcErrMsg);
            break;
        case MainChoice::QUIT:
            QuitMsg();
            break;
        default:
            SelectionError();
            break;
        }
    } while (mainMenu != MainChoice::QUIT);


    // Pointer array to nullptr.
    for (int i = 0; i < MAX_SIZE; i++)
    {
        ptrRec[i] = nullptr;
    }


    return 0;
}




