
#ifndef RECORDFUNCTIONS_H
#define RECORDFUNCTIONS_H

#include "Record.h"
#include "RecordArray.h"

void DisplayErrFile();
// Reads and prints error file to the screen.
// Precondition: "error.txt" is available to read from.
// Postcondition: Prints the error file to the screen.

void ReadFile(RecordArray& recArr_in, Record* pArr[], string errMsgs[], int& arrSize, int& errSize,
	string& id_err, string& mod_err, string& quant_err, string& prc_err);
// Reads and validates entries from the input file.
// Precondition: "record.txt" must be available to read input from.
// Postcondition: Validated records from  input file are written to the main record array.

void RawReadFile(RecordArray& recArr_in, int& arrSize);
// Reads entries from the input file (does not validate).
// Precondition: "record.txt" must be available to read input from.
// Postcondition: All records from input file whether valid or not are written to a raw record array.

void WriteErrorFile(string errMsgs[], const int& errSize);
// Writes errors/error messages to error file.

void WriteFile(RecordArray& recArr_in, const int& arrSize);
// Writes to the output file (replaces all).

void WriteAppendFile(RecordArray& recArr_in, const int& arrSize);
//	Appends entries to the output file.

bool IDValid(string id, string& err);
// Validates input file and user input for each record.
// Returns true if input is valid, otherwise returns false and writes a description of
// the error to errors.txt and to the screen.
// Validates ID.

bool ModelValid(string model, string& err);
// Validates Model.

bool QuantityValid(string quant, string& err);
// Validates Quantity.

bool PriceValid(string prc, string& err);
// Validates Price.

void Print(const RecordArray& recArr_in, const int& arrSize);
// Prints the entries to the screen.
// Precondition: Takes a Record array object and array size is passed by reference.
// Postcondition: Prints the formatted Record array object to the screen.

void PrintRecord(Record rec);
// Prints a single record.

string ToString(Record& rec);
// Formats a Record for output to a file or the screen.
// Precondition: Calling the file uses stringstream to format the Record object.
// Postcondition: Returns a formatted string.

string ToLower(string target);
// returns a string in lowercase.
  
string ToUpper(string target);
// returns a string in uppercase. 

void SearchRec(const RecordArray& recArr_in, Record searchArr[], const int& sizeUsed, int& searchSize, string target);
// Uses linear search and partial search to search a Record for a string.

int SearchID(const RecordArray& recArr_in, const int& arrSize, string target);
// Uses linear search to search for ID. Returns the index of ID if found.
// Otherwise returns -1.

bool IDExists(const RecordArray& recArr_in, const int& arrSize, string id);
// Uses linear search to determine whether ID is in use
// Returns true if ID exists otherwise returns false.

void PrintSearchResults(Record arr[], const int& arrSize);
// Print search results to the screen.

void BubbleSort(Record* [], int, bool(*cmp)(const Record*, const Record*));
// Standard bubble sort function.
// Takes a pointer to an array of objects, the size of the array, and a pointer to a compare lambda expression.
// as argumants.

void SortWrpr(Record* ptrRec[], int& arrSize);
// Sort Wrapper function.

void PrintSorted(Record* arr[], const int arrSize);
// Prints an array of pointer to Records to the screen.

/**************************************************************************************************************/

// Functions for switch statements on main menu:
void PrintAll(const RecordArray& recArr, int& arrSize);
void PrintInvalid(int& err);
void Search(const RecordArray& recArr_in, const int& sizeUsed);
void ManageItem(RecordArray& recArr_in, Record* pArr[], RecordArray& inputArr_in, RecordArray& rawArr_in, string errMsgs[], 
				int& arrSize, int& arrSize_in, int& rawSize, int& errSize, string& id_err, string& mod_err, 
				string& quant_err, string& prc_err);
void QuitMsg();
void SelectionError();	// User input errors.


// Functions for switch statements on sort menu.
// Uses parallel array of pointers and lambda expressions for sorting.
void SortID(Record* arr[], int& arrSize);
void SortModel(Record* arr[], int& arrSize);
void SortQuantity(Record* arr[], int& arrSize);
void SortPrice(Record* arr[], int& arrSize);


// Functions for switch statements on item management menu.
Record InputRecord(RecordArray& recArr_in, int& arrSize, string& id_err, 
				string& mod_err, string& quant_err, string& prc_err);	// Input new records to input array.
string InputID(RecordArray& recArr_in, int& arrSize, string& id_err);
string InputModel(string& mod_err);
string InputQuantity(string& quant_err);
string InputPrice(string& prc_err);


// Functions for edit record menu.
void EditRecord(RecordArray& recArr_in, Record* pArr[], RecordArray& inputArr_in, RecordArray& rawArr_in, string errMsgs[],
			int& arrSize, int& arrSize_in, int& rawSize, int& errSize, string& id_err, string& mod_err,
			string& quant_err, string& prc_err);	// Edits a record from the record file.
void DeleteRecord(RecordArray& recArr_in, int& arrSize, string& id_err);	// Deletes a record from the record file.
void PrintRecord(RecordArray& recArr_in, int& arrSize);	// Prints newly entered records from input array.
void SaveRecord(RecordArray& recArr_in, int& arrSize);	// Appends new records to the record file.



#endif // !RECORDFUNCTIONS_H
