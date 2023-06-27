
#ifndef INTERFACE_H
#define INTERFACE_H

#include "RecordFunctions.h"

// Enumerations.
enum class WelcomeChoice { ARRAY_TYPE = 1, LIST_TYPE = 2, QUIT_WELCOME = 3 };
enum class MainChoice { PRINT_ALL = 1, PRINT_INVALID = 2, SEARCH = 3, SORT = 4, MANAGE_ITEM = 5, QUIT = 6 };
enum class SortChoice { SORT_ID = 1, SORT_MODEL = 2, SORT_QUANTITY = 3, SORT_PRICE = 4, PREVIOUS_MENU = 5 };
enum class ItemChoice { INPUT_ITEM = 1, EDIT_ITEM = 2, DELETE_ITEM = 3, PRINT_ITEM = 4, SAVE_ITEM = 5, PREV_MENU = 6 };
enum class EditChoice { EDIT_ID = 1, EDIT_MODEL = 2, EDIT_QUANTITY = 3, EDIT_PRICE = 4, EDIT_RECORD = 5, DISPLAY_RECORD = 6, SAVE_RECORD = 7, BACK_PREV = 8 };

int MenuUserInput();
// Function for User input on menus.

string YesNoUserInput();
// Function for yes or no responses from user.

void DisplayWelcomeMenu();
// Introduces the program and displays the initial menu.

void DisplayMainMenu();
// Displays the main menu to the screen.

void DisplaySortMenu();
// Displays the Sort sub menu.

void DisplayManageItemMenu();
// Displays the item management menu.

void DisplayEditItemMenu();
// Displays the edit item menu.

/*************************************** -- Switch Statement Functions-- **************************************/

void SwitchWelcomeMenu(InvStorage& inv, ErrMsgs& err);
// Switch statements for Welcome Menu.

void SwitchMainMenu(InvStorage& inv, ErrMsgs& err);
// Switch statements for main menu.

void SwitchSortMenu(Record* ptrRec[], int& arrSize);
// Switch statements for Sort Menu.

void SortID(Record* arr[], int& arrSize);
void SortModel(Record* arr[], int& arrSize);
void SortQuantity(Record* arr[], int& arrSize);
void SortPrice(Record* arr[], int& arrSize);
// Functions for switch statements on sort menu.
// Uses parallel array of pointers and lambda expressions for sorting.

void SwitchManageItemMenu(InvStorage& inv, ErrMsgs& err);
// Switch statements for Manage Item Menu.

Record InputRecord(InvStorage& inv, ErrMsgs& err);
string InputID(InvStorage& inv, ErrMsgs& err);
string InputModel(ErrMsgs& err);
string InputQuantity(ErrMsgs& err);
string InputPrice(ErrMsgs& err);
// Functions used by switch statements on Manage Item Menu.

void SwitchEditRecord(InvStorage& inv, ErrMsgs& err);	// Edits a record from the record file.
// Switch statements for Edit Record Menu.

void DeleteRecord(InvStorage& inv, ErrMsgs& err);	// Deletes a record from the record file.
void PrintInputRecord(InvStorage& inv);	// Prints newly entered records from input array.
void SaveRecord(InvStorage& inv);	// Appends new records to the record file.
// Functions for edit record menu.

void QuitMsg();	// final Message before quitting. 
void SelectionError();	// User input error while selecting from menus.

#endif	//!INTERFACE_H