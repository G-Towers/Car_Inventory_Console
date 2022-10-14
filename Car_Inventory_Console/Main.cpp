// Car Inventory

//#include "Record.h"
#include "RecordFunctions.h"


int main()
{
    int count = 0;  // Array size for carRec.
    int rawCount = 0;   // Size for raw array.
    int errCount = 0;    // How many records with errors in file.
    int inputCount = 0; // Array size for inputRec.

    // For user input.
    string stringInput = "";
    int intInput = 0;

    // Error message strings.
    string idErrMsg = "";
    string mdlErrMsg = "";
    string quantErrMsg = "";
    string prcErrMsg = "";

    // Array of error messages.
    string errorMsgs[MAX_ERR_MSG] = { "" };

    // Daclare array objects.
    Record* carRec = new Record[MAX_SIZE];  // Main record array of automobiles allocated dynamically.
    Record* rawCarRec = new Record[MAX_SIZE];   // Array for unaltered record file.
    Record* ptrRec[MAX_SIZE] = { nullptr };   // Parallel array of pointers.
    Record inputRec[MAX_SIZE];  // Temp record array for new records.

    // Read and validate the inventory of automobiles from the file.
    ReadFile(carRec, ptrRec, errorMsgs, count, errCount, idErrMsg,
        mdlErrMsg, quantErrMsg, prcErrMsg);

    // Read everything into a separate array.
    RawReadFile(rawCarRec, rawCount);

    MainChoice mainMenu = MainChoice::PRINT_ALL;  // Menu enum

    do
    {
        // Display the menu and prompt user for input.
        DisplayMainMenu();
        getline(cin, stringInput);

        // Check if nothing is entered.
        while (stringInput == "")
        {
            cout << "\nYou didn't enter anything!\n";
            cout << "\nEnter your selection: ";
            getline(cin, stringInput);
        }

        // Check if too many characters are entered.
        while (stringInput.length() > 2)
        {
            cout << "\nYou entered too many characters!\n";
            cout << "\nEnter your selection: ";
            getline(cin, stringInput);
        }

        // Convert string to integer.
        intInput = atoi(stringInput.c_str());

        mainMenu = (MainChoice)intInput; // cast to enum type.

        switch (mainMenu)
        {
        case MainChoice::PRINT_ALL:
            ReadFile(carRec, ptrRec, errorMsgs, count, errCount, idErrMsg,
                    mdlErrMsg, quantErrMsg, prcErrMsg);
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


    return 0;
}




