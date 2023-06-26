
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

void DisplayItemMenu();
// Displays the item management menu.

void DisplayEditItemMenu();
// Displays the edit item menu.

// -- Switch Statement Functions --
//

void SwitchWelcomeMenu(RecordArray& recArr, Record* pArr[], RecordArray& inArr, RecordArray& rawArr, int& size,
	int& inSize, int& rawSize, string errMsgs[], int& errSize, string& id_err, string& mod_err, string& quant_err,
	string& prc_err);
// Switch statements for Welcome Menu.

void SwitchMainMenu(RecordArray& recArr, Record* pArr[], RecordArray& inArr, RecordArray& rawArr, int& size, 
	int& inSize, int& rawSize, string errMsgs[], int& errSize, string& id_err, string& mod_err, string& quant_err, 
	string& prc_err);
// Switch statements for main menu.

#endif	//!INTERFACE_H