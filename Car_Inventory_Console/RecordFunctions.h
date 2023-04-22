// #pragma once
#ifndef RECORDFUNCTIONS_H
#define RECORDFUNCTIONS_H

#include "Record.h"

// Function for User input on menus.
int MenuUserInput();

// Displays the main menu to the screen.
void DisplayMainMenu();

// Displays the Sort sub menu.
void DisplaySortMenu();

// Displays the item management menu.
void DisplayItemMenu();

// Displays the edit item menu.
void DisplayEditItemMenu();

// Reads and prints error file to the screen.
// Precondition: "error.txt" is available to read from.
// Postcondition: Prints the error file to the screen.
void DisplayErrFile();

// Reads and validates entries from the input file.
// Precondition: "record.txt" must be available to read input from.
// Postcondition: Validated records from  input file are written to the main record array.
void ReadFile(Record arr[], Record* pArr[], string errMsgs[], int& arrSize, int& errSize,
	string& id_err, string& mod_err, string& quant_err, string& prc_err);

// Reads entries from the input file (does not validate).
// Precondition: "record.txt" must be available to read input from.
// Postcondition: All records from input file whether valid or not are written to a raw record array.
void RawReadFile(Record arr[], int& arrSize);

// Writes errors/error messages to error file.
void WriteErrorFile(string errMsgs[], const int& errSize);

// Writes to the output file (replaces all).
void WriteFile(Record arr[], const int& arrSize);

//	Appends entries to the output file.
void WriteAppendFile(Record arr[], const int& arrSize);

// Validates input file and user input for each record.
// Returns true if input is valid, otherwise returns false and writes a description of
// the error to errors.txt and to the screen.
// Validates ID.
bool IDValid(string id, string& err);

// Validates Model.
bool ModelValid(string model, string& err);

// Validates Quantity.
bool QuantityValid(string quant, string& err);

// Validates Price.
bool PriceValid(string prc, string& err);

// Prints the entries to the screen.
// Precondition: Takes a Record array object and array size is passed by reference.
// Postcondition: Prints the formatted Record array object to the screen.
void Print(Record arr[], const int& arrSize);

// Prints a single record.
void PrintRecord(Record rec);

// Formats a Record for output to a file or the screen.
// Precondition: Calling the file uses stringstream to format the Record object.
// Postcondition: Returns a formatted string.
string ToString(Record& rec);

// returns a string in lowercase.
string ToLower(string target);

// returns a string in uppercase.   
string ToUpper(string target);

// Uses linear search and partial search to search a Record for a string.
void SearchRec(const Record arr[], Record searchArr[], const int& sizeUsed, int& searchSize, string target);

// Uses linear search to search for ID. Returns the index of ID if found.
// Otherwise returns -1.
int SearchID(const Record arr[], const int& arrSize, string target);

// Uses linear search to determine whether ID is in use
// Returns true if ID exists otherwise returns false.
bool IDExists(const Record arr[], const int& arrSize, string id);

// Print search results to the screen.
void PrintSearchResults(Record arr[], const int& arrSize);

// Standard bubble sort function.
// Takes a pointer to an array of objects, the size of the array, and a pointer to a compare lambda expression.
// as argumants.
void BubbleSort(Record* [], int, bool(*cmp)(const Record*, const Record*));

// Sort Wrapper function.
void SortWrpr(Record* ptrRec[], int& arrSize);

// Prints an array of pointer to Records to the screen.
void PrintSorted(Record* arr[], const int arrSize);

// Functions for switch statements on main menu:
void PrintAll(Record arr[], int& arrSize);
void PrintInvalid(int& err);
void Search(const Record arr[], const int& sizeUsed);
void ManageItem(Record arr[], Record* pArr[], Record arr_in[], Record rawArr[], string errMsgs[], 
				int& arrSize, int& arrSize_in, int& rawSize, int& errSize,
				string& id_err, string& mod_err, string& quant_err, string& prc_err);
void QuitMsg();
void SelectionError();	// User input errors.

// Functions for switch statements on sort menu.
// Uses parallel array of pointers and lambda expressions for sorting.
void SortID(Record* arr[], int& arrSize);
void SortModel(Record* arr[], int& arrSize);
void SortQuantity(Record* arr[], int& arrSize);
void SortPrice(Record* arr[], int& arrSize);

// Functions for switch statements on item management menu.
Record InputRecord(Record arr[], int& arrSize, string& id_err, 
				string& mod_err, string& quant_err, string& prc_err);	// Input new records to input array.
string InputID(Record arr[], int& arrSize, string& id_err);
string InputModel(string& mod_err);
string InputQuantity(string& quant_err);
string InputPrice(string& prc_err);

void EditRecord(Record arr[], int& arrSize, string& id_err, string& mod_err, 
				string& quant_err, string& prc_err);	// Edits a record from the record file.
void DeleteRecord(Record arr[], int& arrSize, string& id_err);	// Deletes a record from the record file.
void PrintRecord(Record arr[], int& arrSize);	// Prints newly entered records from input array.
void SaveRecord(Record arr[], int& arrSize);	// Appends new records to the record file.

// Functions for edit record menu.



#endif // !RECORDFUNCTIONS_H
