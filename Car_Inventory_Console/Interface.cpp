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


void DisplayMainMenu()
{
    // Display main menu.
    cout << "\n-- Car Inventory -- \n"
        << "\n1. Display Records on file.\n"
        << "2. Display Invalid Records.\n"
        << "3. Search Records.\n"
        << "4. Sort Records.\n"
        << "5. Manage Records.\n"
        << "6. Quit\n" << endl;
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