#ifndef INVFUNCTIONS_H
#define INVFUNCTIONS_H

#include "InvList.h"
#include "ErrMsgs.h"

string ToStringKey(const Node* nod);
// Formats a Record + Key for output to a file or the screen.
// Precondition: Calling the file uses stringstream to format the Record object.
// Postcondition: Returns a formatted string.

void ReadFileList(InvList& lstItem, ErrMsgs& err);
// Reads and validates entries from the input file.
// Precondition: "record.txt" must be available to read input from.
// Postcondition: Validated records from  input file are written to the linked list.

void WriteFileList(InvList& lstItem);
// Writes to the output file (replaces all).

void Search(InvList& lstItem);
// Search function for linked list switch statement.

void SearchList(InvList& lstItem, InvList& searchList, string target);
// Uses linear search and partial search to search the list for a string.
// Puts results from search into searchList.

int SearchIDList(const InvList& lstItem, string target);
// Uses linear search to search for ID. Returns the Key of ID if found.
// Otherwise returns -1.

bool IDExistsList(const InvList& lstItem, const int& list_size, string id);
// Uses linear search to determine whether ID is in use.
// Returns true if ID exists otherwise returns false.

void PrintList(const InvList& list);
// Prints the list.

void PrintListRecord(const Node* nod);
// Prints a single record in a list.

void PrintSearchResultsList(const InvList& list);
// Print search results to the screen.

Node* SwapPtr(Node* ptr1, Node* ptr2);
// Swaps nodes. Used with BubbleSort.
// Returns a Node pointer

void BubbleSortList(Node** head_in, int list_size, bool(*cmp)(const Node*, const Node*));
// Standard bubble sort function.
// Takes a pointer to pointer of head of list, the size of the list, 
// and a pointer to a compare lambda expression as argumants.


#endif // !INVFUNCTIONS_H
