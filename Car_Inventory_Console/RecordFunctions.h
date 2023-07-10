// Array-based Record functions.

#ifndef RECORDFUNCTIONS_H
#define RECORDFUNCTIONS_H

#include "Record.h"
#include "RecordArray.h"
#include "InvStorage.h"
#include "ErrMsgs.h"


void DisplayErrFile();
// Reads and prints error file to the screen.
// Precondition: "error.txt" is available to read from.
// Postcondition: Prints the error file to the screen.

void ReadFile(InvStorage& inv, ErrMsgs& err);
// Reads and validates entries from the input file.
// Precondition: "record.txt" must be available to read input from.
// Postcondition: Validated records from  input file are written to the main record array.

void RawReadFile(InvStorage& inv);
// Reads entries from the input file (does not validate).
// Precondition: "record.txt" must be available to read input from.
// Postcondition: All records from input file whether valid or not are written to a raw record array.

void WriteErrorFile(ErrMsgs& err);
// Writes errors/error messages to error file.

void WriteFile(InvStorage& inv);
// Writes to the output file (replaces all).
// Uses raw record array (leaves everything on file intact).

void WriteAppendFile(InvStorage& inv);
// Appends entries to the output file.
// Uses car record array (valid records).

bool IDValid(string id);
// Validates ID string.
// Returns true if ID string is valid, otherwise returns false.

bool IDValid(string id, ErrMsgs& err);
// Validates ID string (overloaded).
// Returns true if string is valid, otherwise returns false and writes a description of
// the error to ErrMsgs object.

bool ModelValid(string mod);
// Validates model.

bool ModelValid(string model, ErrMsgs& err);
// Validates model (overloaded).

bool QuantityValid(string quant);
// Validates quantity.

bool QuantityValid(string quant, ErrMsgs& err);
// Validates quantity (overloaded).

bool PriceValid(string prc);
// Validates price.

bool PriceValid(string prc, ErrMsgs& err);
// Validates price (overloaded).

void Print(const InvStorage& inv);
// Prints the entries to the screen.
// Precondition: Takes a Record array object and array size is passed by reference.
// Postcondition: Prints the formatted Record array object to the screen.

void PrintRecord(Record& rec);
// Prints a single record.

string ToString(const Record& rec);
// Formats a Record for output to a file or the screen.
// Precondition: Calling the file uses stringstream to format the Record object.
// Postcondition: Returns a formatted string.

string ToLower(string target);
// returns a string in lowercase.
  
string ToUpper(string target);
// returns a string in uppercase. 

void SearchRec(const InvStorage& inv, RecordArray& searchArr, string target);
// Uses linear search and partial search to search a Record for a string.

int SearchID(const InvStorage& inv, string target);
// Uses linear search to search for ID. Returns the index of ID if found.
// Otherwise returns -1.

bool IDExists(const InvStorage& inv, string id);
// Uses linear search to determine whether ID is in use
// Returns true if ID exists otherwise returns false.

void PrintSearchResults(const RecordArray& arr);
// Print search results to the screen.

void BubbleSort(Record* [], int, bool(*cmp)(const Record*, const Record*));
// Standard bubble sort function.
// Takes a pointer to an array of objects, the size of the array, and a pointer to a compare lambda expression.
// as argumants.

void PrintSorted(Record* arr[], const int arrSize);
// Prints an array of pointer to Records to the screen.

/**************************************************************************************************************/

// Functions for switch statements on main menu:
void PrintAll(const InvStorage& inv);
void PrintInvalid(int& err);
void Search(const InvStorage& inv);


#endif // !RECORDFUNCTIONS_H
