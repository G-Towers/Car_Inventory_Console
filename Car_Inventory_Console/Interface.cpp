// Implementation of Interface.

#include "Interface.h"
#include "InvStorage.h"
#include "ErrMsgs.h"


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

void DisplayManageItemMenu()
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

void SwitchWelcomeMenu(InvStorage& inv, ErrMsgs& err)
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
            ReadFile(inv, err);
            SwitchMainMenu(inv, err);
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

void SwitchMainMenu(InvStorage& inv, ErrMsgs& err)
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
            PrintAll(inv);
            break;
        case MainChoice::PRINT_INVALID:
            PrintInvalid(err.errCount);
            break;
        case MainChoice::SEARCH:
            Search(inv);
            break;
        case MainChoice::SORT:
            SwitchSortMenu(inv.ptrRec, inv.carCount);
            break;
        case MainChoice::MANAGE_ITEM:
            SwitchManageItemMenu(inv, err);
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

void SwitchSortMenu(Record* ptrRec[], int& arrSize)
{
    SortChoice sortMenu = SortChoice::SORT_ID;

    do
    {
        DisplaySortMenu();
        int userInput = MenuUserInput();    // user input.
        sortMenu = (SortChoice)userInput; // cast to enum type.

        switch (sortMenu)
        {
        case SortChoice::SORT_ID:
            SortID(ptrRec, arrSize);
            break;
        case SortChoice::SORT_MODEL:
            SortModel(ptrRec, arrSize);
            break;
        case SortChoice::SORT_QUANTITY:
            SortQuantity(ptrRec, arrSize);
            break;
        case SortChoice::SORT_PRICE:
            SortPrice(ptrRec, arrSize);
            break;
        case SortChoice::PREVIOUS_MENU:
            break;
        default:
            SelectionError();
            break;
        }
    } while (sortMenu != SortChoice::PREVIOUS_MENU);

}

void SortID(Record* ptrArr[], int& arrSize)
{
    cout << "\nSort by ID number --\n" << endl;

    // Bubble sort using lambda expression.
    BubbleSort(ptrArr, arrSize, [](const Record* r1, const Record* r2)
        { return ToLower(r1->GetID()) > ToLower(r2->GetID()); });

    PrintSorted(ptrArr, arrSize);
}

void SortModel(Record* ptrArr[], int& arrSize)
{
    cout << "\nSort by model --\n" << endl;


    BubbleSort(ptrArr, arrSize, [](const Record* r1, const Record* r2)
        { return ToLower(r1->GetModel()) > ToLower(r2->GetModel()); });

    PrintSorted(ptrArr, arrSize);
}

void SortQuantity(Record* ptrArr[], int& arrSize)
{
    cout << "\nSort by quantity --\n" << endl;

    BubbleSort(ptrArr, arrSize, [](const Record* r1, const Record* r2)
        { return r1->GetQuantity() > r2->GetQuantity(); });

    PrintSorted(ptrArr, arrSize);
}

void SortPrice(Record* ptrArr[], int& arrSize)
{
    cout << "\nSort by price --\n" << endl;

    BubbleSort(ptrArr, arrSize, [](const Record* r1, const Record* r2)
        { return r1->GetPrice() > r2->GetPrice(); });

    PrintSorted(ptrArr, arrSize);
}

void SwitchManageItemMenu(InvStorage& inv, ErrMsgs& err)
{
    Record tempRec;
    ItemChoice ItemMenu = ItemChoice::INPUT_ITEM;

    do
    {
        DisplayManageItemMenu();
        int userInput = MenuUserInput();

        ItemMenu = (ItemChoice)userInput; // cast to enum type.

        switch (ItemMenu)
        {
        case ItemChoice::INPUT_ITEM:
            tempRec = InputRecord(inv, err);
            if (tempRec.GetID() == "r" || tempRec.GetModel() == "r" ||
                tempRec.GetQuantity() == 114 || tempRec.GetPrice() == 114.0)
            {
                cout << "\nAborted..." << endl;
                break;
            }
            else
            {
                inv.inputRec[inv.inputCount] = tempRec;
                inv.inputCount++;
                break;
            }

        case ItemChoice::EDIT_ITEM:
            SwitchEditRecord(inv, err);
            break;
        case ItemChoice::DELETE_ITEM:
            DeleteRecord(inv, err);
            ReadFile(inv, err);
            break;
        case ItemChoice::PRINT_ITEM:
            PrintInputRecord(inv);
            break;
        case ItemChoice::SAVE_ITEM:
            SaveRecord(inv);
            inv.ResetInputArr();
            ReadFile(inv, err);
            break;
        case ItemChoice::PREV_MENU:
            break;
        default:
            SelectionError();
            break;
        }
    } while (ItemMenu != ItemChoice::PREV_MENU);

}

Record InputRecord(InvStorage& inv, ErrMsgs& err)
{
    string id = "", mod = "", quant = "", prc = "";
    Record tempRec; // Temporary Record.

    id = InputID(inv, err);
    if (id == "r")
    {
        tempRec.SetID(id);
        return tempRec;
    }
    else
        tempRec.SetID(id);

    mod = InputModel(err);
    if (mod == "r")
    {
        tempRec.SetModel(mod);
        return tempRec;
    }
    else
        tempRec.SetModel(mod);

    quant = InputQuantity(err);
    if (quant == "r")
    {
        int quantR = int(quant[0]);     // Convert string to int.
        tempRec.SetQuantity(quantR);    // Set int to Record object.
        return tempRec;
    }
    else
        tempRec.SetQuantity(stoi(quant));

    prc = InputPrice(err);
    if (prc == "r")
    {
        float prcR = float(prc[0]);
        tempRec.SetPrice(prcR);
        return tempRec;
    }
    else
        tempRec.SetPrice(stof(prc));


    return tempRec;

}

string InputID(InvStorage& inv, ErrMsgs& err)
{
    string id = "";

    // Prompt the user for ID.
    cout << "\nCar ID's are 7 characters long,\n"
        << "The first 2 characters must be letters A - F.\n"
        << "\nEnter a unique ID ( r to return to menu): ";
    getline(cin, id);

    if (id == "r" || id == "R")
        return id;

    // Check if nothing is entered.
    while (id == "")
    {
        cout << "\nYou didn't enter anything!\n";
        cout << "\nEnter ID: ";
        getline(cin, id);

        if (id == "r" || id == "R")
            return id;
    }

    while (!IDValid(id, err))
    {
        cout << "\nID invalid...\n"
            << "\n" << err.idErrMsg << "\n";
        cout << "\nEnter ID: ";
        getline(cin, id);

        if (id == "r" || id == "R")
            return id;

        // Check if nothing is entered again.
        while (id == "")
        {
            cout << "\nYou didn't enter anything!\n";
            cout << "\nEnter ID: ";
            getline(cin, id);

            if (id == "r" || id == "R")
                return id;
        }

        // Check if ID exists.
        while (IDExists(inv, id))
        {
            cout << "\nThat ID is already in use." << endl;
            cout << "\nEnter ID: ";
            getline(cin, id);

            if (id == "r" || id == "R")
                return id;

            // Check if nothing is entered again.
            while (id == "")
            {
                cout << "\nYou didn't enter anything!\n";
                cout << "\nEnter ID: ";
                getline(cin, id);

                if (id == "r" || id == "R")
                    return id;
            }

        }

    }

    // Check if ID exists.
    while (IDExists(inv, id))
    {
        cout << "\nThat ID is already in use." << endl;
        cout << "\nEnter ID: ";
        getline(cin, id);

        if (id == "r" || id == "R")
            return id;

        // Check if nothing is entered again.
        while (id == "")
        {
            cout << "\nYou didn't enter anything!\n";
            cout << "\nEnter ID: ";
            getline(cin, id);

            if (id == "r" || id == "R")
                return id;
        }

        while (!IDValid(id, err))
        {
            cout << "\nID invalid...\n"
                << "\n" << err.idErrMsg << "\n";
            cout << "\nEnter ID: ";
            getline(cin, id);

            if (id == "r" || id == "R")
                return id;

            // Check if nothing is entered again.
            while (id == "")
            {
                cout << "\nYou didn't enter anything!\n";
                cout << "\nEnter ID: ";
                getline(cin, id);

                if (id == "r" || id == "R")
                    return id;
            }

        }

    }

    return id;
}

string InputModel(ErrMsgs& err)
{
    string mod;

    // Prompt the user for Model.
    cout << "\nModel Names must be alpha-numeric and may contain underscores ( _ ),\n"
        << "However, the model name must start with an alpha character and cannot\n"
        << "have blank spaces.\n"
        << "\nEnter Model: ";
    getline(cin, mod);

    if (mod == "r" || mod == "R")
        return mod;

    // Check if nothing is entered.
    while (mod == "")
    {
        cout << "\nYou didn't enter anything!\n";
        cout << "\nEnter Model: ";
        getline(cin, mod);

        if (mod == "r" || mod == "R")
            return mod;
    }

    while (!ModelValid(mod, err))
    {
        cout << "\nModel invalid...\n"
            << "\n" << err.mdlErrMsg << "\n";
        cout << "\nEnter Model: ";
        getline(cin, mod);

        if (mod == "r" || mod == "R")
            return mod;

        // Check if nothing is entered again.
        while (mod == "")
        {
            cout << "\nYou didn't enter anything!\n";
            cout << "\nEnter Model: ";
            getline(cin, mod);

            if (mod == "r" || mod == "R")
                return mod;
        }
    }

    return mod;
}

string InputQuantity(ErrMsgs& err)
{
    string quant;

    // Prompt user for quantity.
    cout << "\nEnter quantity of items: ";
    getline(cin, quant);

    if (quant == "r" || quant == "R")
        return quant;

    // Check if nothing is entered.
    while (quant == "")
    {
        cout << "\nYou didn't enter anything!\n";
        cout << "\nEnter Quantity: ";
        getline(cin, quant);

        if (quant == "r" || quant == "R")
            return quant;
    }

    while (!QuantityValid(quant, err))
    {
        cout << "\nQuantity invalid...\n"
            << "\n" << err.quantErrMsg << "\n";
        cout << "\nEnter Quantity: ";
        getline(cin, quant);

        if (quant == "r" || quant == "R")
            return quant;

        // Check if nothing is entered again.
        while (quant == "")
        {
            cout << "\nYou didn't enter anything!\n";
            cout << "\nEnter Quantity: ";
            getline(cin, quant);

            if (quant == "r" || quant == "R")
                return quant;
        }
    }

    return quant;
}

string InputPrice(ErrMsgs& err)
{
    string prc;

    // Prompt user for price.
    cout << "\nEnter price of item: ";
    getline(cin, prc);

    if (prc == "r" || prc == "R")
        return prc;

    // Check if nothing is entered.
    while (prc == "")
    {
        cout << "\nYou didn't enter anything!\n";
        cout << "\nEnter Price: ";
        getline(cin, prc);

        if (prc == "r" || prc == "R")
            return prc;
    }

    while (!PriceValid(prc, err))
    {
        cout << "\nPrice invalid...\n"
            << "\n" << err.prcErrMsg << "\n";
        cout << "\nEnter Price: ";
        getline(cin, prc);

        if (prc == "r" || prc == "R")
            return prc;

        // Check if nothing is entered again.
        while (prc == "")
        {
            cout << "\nYou didn't enter anything!\n";
            cout << "\nEnter Price: ";
            getline(cin, prc);

            if (prc == "r" || prc == "R")
                return prc;
        }
    }

    return prc;
}

void SwitchEditRecord(InvStorage& inv, ErrMsgs& err)
{
    string idEdit, modEdit, quantEdit, prcEdit; // Store edited input.
    Record tempRec; // Temporary Record to hold the Record being edited.
    Record tempRecEdit; // Temporary Record to hold edited changes to Record being edited.

    string editID;  // Search ID to locate record.
    string recResp; //  User response to edit record.

    int quantR;
    float prcR;

    cout << "\nEnter ID of record to edit: ";
    getline(cin, editID);

    // Check if nothing is entered.
    while (editID == "")
    {
        cout << "\nYou didn't enter anything!\n";
        cout << "\nEnter ID: ";
        getline(cin, editID);
    }

    // Search for the ID.
    int index = SearchID(inv, editID);

    if (index == -1)
    {
        cout << "\nRecord not Found." << endl;
    }

    else
    {
        cout << "\nRecord found: " << inv.rawCarRec[index].GetID() << " -- "
            << inv.rawCarRec[index].GetModel() << " -- " << inv.rawCarRec[index].GetQuantity() << " -- "
            << inv.rawCarRec[index].GetPrice() << "\n"
            << "Index: " << index << endl;

        cout << "\nEdit this record? (y/n):";
        recResp = YesNoUserInput();

        if (recResp == "Y" || recResp == "YES")
        {
            int editInput;   // user input for sub menu.
            EditChoice editMenu = EditChoice::EDIT_ID;   // Initialize.

            // Store temporary record.
            tempRec.SetID(inv.rawCarRec[index].GetID());
            tempRec.SetModel(inv.rawCarRec[index].GetModel());
            tempRec.SetQuantity(inv.rawCarRec[index].GetQuantity());
            tempRec.SetPrice(inv.rawCarRec[index].GetPrice());

            do
            {
                DisplayEditItemMenu();
                editInput = MenuUserInput();

                editMenu = (EditChoice)editInput; // cast to enum type.

                switch (editMenu)
                {
                case EditChoice::EDIT_ID:
                    idEdit = InputID(inv, err);
                    tempRecEdit.SetID(idEdit);
                    if (tempRecEdit.GetID() == ToLower("r"))
                    {
                        cout << "\nAborted..." << endl;
                        break;
                    }
                    else
                    {
                        tempRec.SetID(idEdit);
                        cout << "\nID successfully updated." << endl;
                    }
                    break;
                case EditChoice::EDIT_MODEL:
                    modEdit = InputModel(err);
                    tempRecEdit.SetModel(modEdit);
                    if (tempRecEdit.GetModel() == ToLower("r"))
                    {
                        cout << "\nAborted..." << endl;
                        break;
                    }
                    else
                    {
                        tempRec.SetModel(modEdit);
                        cout << "\nModel successfully updated." << endl;
                    }

                    break;
                case EditChoice::EDIT_QUANTITY:
                    quantEdit = InputQuantity(err);
                    quantR = int(quantEdit[0]);     // Convert string to int.
                    tempRecEdit.SetQuantity(quantR);    // Set int to Record object.
                    if (tempRecEdit.GetQuantity() == 114)
                    {
                        cout << "\nAborted..." << endl;
                        break;
                    }
                    else
                    {
                        tempRec.SetQuantity(quantR);
                        cout << "\nQuantity successfully updated." << endl;
                    }
                    break;
                case EditChoice::EDIT_PRICE:
                    prcEdit = InputPrice(err);
                    prcR = float(prcEdit[0]);     // Convert string to float.
                    tempRecEdit.SetPrice(prcR);    // Set float to Record object.
                    if (tempRecEdit.GetPrice() == 114.0)
                    {
                        cout << "\nAborted..." << endl;
                        break;
                    }
                    else
                    {
                        tempRec.SetPrice(prcR);
                        cout << "\nPrice successfully updated." << endl;
                    }
                    break;
                case EditChoice::EDIT_RECORD:
                    tempRec = InputRecord(inv, err);
                    break;
                case EditChoice::DISPLAY_RECORD:
                    PrintRecord(tempRec);
                    break;
                case EditChoice::SAVE_RECORD:
                    inv.rawCarRec[index] = tempRec;
                    WriteFile(inv);
                    ReadFile(inv, err);
                    cout << "\nRecord replaced." << endl;
                    break;
                case EditChoice::BACK_PREV:
                    break;
                default:
                    SelectionError();
                    break;
                }
            } while (editMenu != EditChoice::BACK_PREV);



        }
    }


}

void DeleteRecord(InvStorage& inv, ErrMsgs& err)
{
    string delID;   // ID to delete.
    string resp;  // User response. 

    cout << "\nEnter ID for record to delete: ";
    getline(cin, delID);

    // Check if nothing is entered.
    while (delID == "")
    {
        cout << "\nYou didn't enter anything!\n";
        cout << "\nEnter ID: ";
        getline(cin, delID);
    }

    while (!IDValid(delID, err))
    {
        cout << "\nID invalid...\n"
            << "\n" << err.idErrMsg << "\n";
        cout << "\nEnter ID: ";
        getline(cin, delID);

        // Check if nothing is entered again.
        while (delID == "")
        {
            cout << "\nYou didn't enter anything!\n";
            cout << "\nEnter ID: ";
            getline(cin, delID);
        }

    }

    int index = SearchID(inv, delID);

    if (index == -1)
    {
        cout << "\nRecord not Found." << endl;
    }

    else
    {
        // Display record if found.
        cout << "\nRecord found: " << inv.carRec[index].GetID() << " "
            << inv.carRec[index].GetModel() << " " << inv.carRec[index].GetQuantity() << " "
            << inv.carRec[index].GetPrice() << "\n"
            << "Index: " << index << endl;

        cout << "\nDelete record on file? (y/n): ";
        resp = YesNoUserInput();


        if (resp == "Y" || resp == "YES")
        {
            for (int i = index; i < inv.carCount - 1; i++)
            {
                inv.carRec[i] = inv.carRec[i + 1];
            }
            inv.carCount--;

            WriteFile(inv);
            cout << "\nRecord deleted." << endl;

        }
    }

}

void PrintInputRecord(InvStorage& inv)
{
    cout << "\nDisplay Entered Records --\n" << endl;
    Print(inv); // Print records to screen.
}

void SaveRecord(InvStorage& inv)
{
    string resp;

    cout << "\nSave to record file? (y/n): ";
    resp = YesNoUserInput();

    if (resp == "Y" || resp == "YES")
    {
        WriteAppendFile(inv);
        cout << "\nRecord saved." << endl;
    }
}


void QuitMsg()
{
    cout << "\nThank you for your time." << endl;
}

void SelectionError()
{
    cout << "\nError! Your selection is invalid." << endl;
    //cin.clear();
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
