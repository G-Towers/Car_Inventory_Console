// Implementation of Interface.

#include "Interface.h"


int MenuUserInput()
{
    // For user input.
    string stringInput = "";
    int intInput = 0;

    // Get user input.
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


    return intInput;
}

string YesNoUserInput()
{
    string stringInput;

    // Get user input.
    getline(cin, stringInput);

    // Check if nothing is entered.
    while (stringInput == "")
    {
        cout << "\nYou didn't enter anything!\n";
        cout << "\nEnter your selection: ";
        getline(cin, stringInput);
    }

    // Check if too many characters are entered.
    while (stringInput.length() > 3)
    {
        cout << "\nYou entered too many characters!\n";
        cout << "\nEnter your selection: ";
        getline(cin, stringInput);
    }

    stringInput = ToUpper(stringInput);
    return stringInput;
}

void DisplayWelcomeMenu()
{
    cout << "\n-- Car Inventory Program --\n"
        << "\n1. Array Implementation.\n"
        << "2. Linked List Implementation.\n" 
        << "3. Quit.\n" << endl;

    cout << "\nEnter Mode of operation: ";
}


void DisplayMainMenu()
{
    // Display main menu.
    cout << "\n-- Record Array implementation -- \n"
        << "\n1. Display Records on file.\n"
        << "2. Display Invalid Records.\n"
        << "3. Search Records.\n"
        << "4. Sort Records.\n"
        << "5. Manage Records.\n"
        << "6. Back to Implementation Selection.\n" << endl;
    cout << "\nEnter your selection: ";

}

void DisplaySortMenu()
{
    // Display the Sort sub-menu.
    cout << "\n-- Sort Records --\n"
        << "\nSort and Display Records By:\n"
        << "1. ID number.\n"
        << "2. Model.\n"
        << "3. Quantity.\n"
        << "4. Price.\n"
        << "5. Back to previous menu.\n" << endl;
    cout << "\nEnter your selection: ";
}

void DisplayItemMenu()
{
    // Display the item management sub-menu.
    cout << "\n-- Inventory Item Management --\n"
        << "\n1. Enter New Item.\n"
        << "2. Edit Items on Record File.\n"
        << "3. Delete Item from Record File.\n"
        << "4. Display Newly Entered Items.\n"
        << "5. Save Items to Record File.\n"
        << "6. Back to Previous Menu.\n" << endl;
    cout << "\nEnter your selection: ";
}

void DisplayEditItemMenu()
{
    // Display the edit item sub-menu.
    cout << "\n-- Edit Record --\n"
        << "\n1. Edit ID.\n"
        << "2. Edit Model.\n"
        << "3. Edit Quantity.\n"
        << "4. Edit Price.\n"
        << "5. Edit Record.\n"
        << "6. Display Edited Record.\n"
        << "7. Save Edited Record to File.\n"
        << "8. Back to Previous Menu.\n" << endl;
    cout << "\nEnter your selection: ";
}

void SwitchWelcomeMenu(RecordArray& recArr, Record* pArr[], RecordArray& inArr, RecordArray& rawArr, int& size,
    int& inSize, int& rawSize, string errMsgs[], int& errSize, string& id_err, string& mod_err, string& quant_err,
    string& prc_err)
{
    WelcomeChoice welcomeMenu = WelcomeChoice::ARRAY_TYPE;  // Wecome menu enum.

    do
    {
        DisplayWelcomeMenu();  // Display the main menu.
        int userInput = MenuUserInput();    // user input.
        welcomeMenu = (WelcomeChoice)userInput; // cast to enum type.

        switch (welcomeMenu)
        {
        case WelcomeChoice::ARRAY_TYPE:
            //ReadFile(carRec, ptrRec, errorMsgs, count, errCount, idErrMsg,
            //       mdlErrMsg, quantErrMsg, prcErrMsg);
            SwitchMainMenu(recArr, pArr, inArr, rawArr, size,
                inSize, rawSize, errMsgs, errSize, id_err, mod_err, quant_err,
                prc_err);
            break;
        case WelcomeChoice::LIST_TYPE:
            
            break;
        case WelcomeChoice::QUIT_WELCOME:
            QuitMsg();
            break;
        default:
            SelectionError();
            break;
        
        }
    } while (welcomeMenu != WelcomeChoice::QUIT_WELCOME);
}

void SwitchMainMenu(RecordArray& recArr, Record* pArr[], RecordArray& inArr, RecordArray& rawArr, int& size,
    int& inSize, int& rawSize, string errMsgs[], int& errSize, string& id_err, string& mod_err, string& quant_err, 
    string& prc_err)
{
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
            PrintAll(recArr, size);
            break;
        case MainChoice::PRINT_INVALID:
            PrintInvalid(errSize);
            break;
        case MainChoice::SEARCH:
            Search(recArr, size);
            break;
        case MainChoice::SORT:
            SortWrpr(pArr, size);
            break;
        case MainChoice::MANAGE_ITEM:
            ManageItem(recArr, pArr, inArr, rawArr, errMsgs, size, inSize,
                rawSize, errSize, id_err, mod_err, quant_err, prc_err);
            break;
        case MainChoice::QUIT:
            QuitMsg();
            break;
        default:
            SelectionError();
            break;
        }
    } while (mainMenu != MainChoice::QUIT);
}
