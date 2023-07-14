
#ifndef INTERFACE_H
#define INTERFACE_H

#include "RecordFunctions.h"
#include "InvFunctions.h"

// Enumerations.
enum class WelcomeChoice { ARRAY_TYPE = 1, LIST_TYPE = 2, QUIT_WELCOME = 3 };
enum class MainChoice { PRINT_ALL = 1, PRINT_INVALID = 2, SEARCH = 3, SORT = 4, MANAGE_ITEM = 5, QUIT = 6 };
enum class SortChoice { SORT_ID = 1, SORT_MODEL = 2, SORT_QUANTITY = 3, SORT_PRICE = 4, SORT_KEY = 5, PREVIOUS_MENU = 6 };
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

void DisplaySortMenuList();
// Display the sort sub menu for Linked lists

void DisplayManageItemMenu();
// Displays the item management menu.

void DisplayEditItemMenu();
// Displays the edit item menu.

/*************************************** -- Switch Statement Functions-- **************************************/

void SwitchWelcomeMenu(InvStorage& inv, InvList& lstItem, ErrMsgs& err);
// Switch statements for Welcome Menu.

void SwitchMainMenu(InvStorage& inv, ErrMsgs& err);
// Switch statements for main menu using arrays.

void SwitchMainMenu(InvList& lstItem, ErrMsgs& err);
// Switch statement for main menu using linked list.

void SwitchSortMenu(Record* ptrRec[], int& arrSize);
// Switch statements for Sort Menu using arrays.

void SwitchSortMenu(InvList& lstItem);
// Switch statements for Sort menu using linked list.

void SwitchManageItemMenu(InvStorage& inv, ErrMsgs& err);
// Switch statements for Manage Item Menu using arrays.

void SwitchManageItemMenu(InvList& lstItem, ErrMsgs& err);
// Switch statements for manage item menu using linked list.

void SwitchEditRecord(InvStorage& inv, ErrMsgs& err);	// Edits a record from the record file.
// Switch statements for Edit Record Menu using arrays.

void SwitchEditRecord(InvList& lstItem, ErrMsgs& err);
// Switch statements for Edit Record Menu using linked list.


/********************************************* -- Sorting Functions -- ***************************************/


void SortID(Record* arr[], int& arrSize);
// Sorts by ID in an array.

void SortID(InvList& lstItem	);
// Sorts by ID in a linked list.

void SortModel(Record* arr[], int& arrSize);
// Sorts by model in an array.

void SortModel(InvList& lstItem);
// Sorts by model in a linked list.

void SortQuantity(Record* arr[], int& arrSize);
// Sorts by quantity in an array.

void SortQuantity(InvList& lstItem);
// Sorts by quantity in a linked list.

void SortPrice(Record* arr[], int& arrSize);
// Sorts by price in an array.

void SortPrice(InvList& lstItem);
//	Sorts by price in a linked list.

void SortKey(InvList& lstItem);
// Sorts by key in a linked list.

// Functions for switch statements on sort menu.
// Uses parallel array of pointers and lambda expressions for sorting.



Record InputRecord(InvStorage& inv, ErrMsgs& err);
Record InputRecord(ErrMsgs& err);	// Input new records to input array.
string InputID(InvStorage& inv, ErrMsgs& err);
string InputID(ErrMsgs& err);
string InputModel(ErrMsgs& err);
string InputQuantity(ErrMsgs& err);
string InputPrice(ErrMsgs& err);
int PromptKey(InvList& lstItem);
// Functions used by switch statements on Manage Item Menu.



void DeleteRecord(InvStorage& inv, ErrMsgs& err);	// Deletes a record from the record file.
void DeleteItem(InvList& lstItem, ErrMsgs& err);	// Deletes a record Item in a linked list.
void PrintInputRecord(InvStorage& inv);	// Prints newly entered records from input array.
void PrintItems();	// Prints list items.
void SaveRecord(InvStorage& inv);	// Appends new records to the record file.
void SaveItems(InvList& lstItem);	// Save Items for linked list.
// Functions for edit record menu.

void QuitMsg();	// final Message before quitting. 
void SelectionError();	// User input error while selecting from menus.

#endif	//!INTERFACE_H