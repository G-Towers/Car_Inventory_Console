#ifndef INVLIST_H
#define INVLIST_H

#include "Node.h"

class InvList
{
public:
	
	InvList() { head = nullptr; }
	// Default constructor that initializes the head to null.
	
	InvList(Node* nod) { head = nod; }	// head will store the address.
	// Constructor with parameter which assigns a pointer to head.

	//~InventoryList() { cout << "List Destructor " << endl; }


	// Access to members.
	Node* GetHead() const { return head; }
	void SetHead(Node* head) { this->head = head; }

	Node* NodeExists(int key);	// Pass key value.
	// Checks if Node exists using key value.
	// Manages whether key value is duplicated or not (key must be unique to each node).
	// The function will either return the address of an existing node if key is found
	// or will return nullptr if not found.
	
	void AppendNode(Node* nod);	// Passes a node by pointer (address).
	// Appends a Node to the list (end of list).

	void PrependNode(Node* nod);
	// Prepends a Node to the list (Attaches at start).

	void InsertNodeAfter(int key, Node* nod);
	// Inserts a node at a specified location (after specified key).

	void DeleteNodeByKey(int key);
	// Deletes a Node by key

	void UpdateNodeByKey(int key, Record rec);
	// Update the node with a new data value.
	// Accesses the node by key value and updates data.

	int GetSize() const { return listSize; }
	// Get the size of the list.

	void SetSize(int size) { listSize = size; }
	// Set the listSize.

	// Overloads.
	void operator++() { ++listSize; }	// prefix
	void operator++(int) { listSize++; }	// postfix
	void operator--() { --listSize; }	// prefix
	void operator--(int) { listSize--; }	// postfix

private:
	Node* head;	// Points to the first node object.
	int listSize = 0;

};

#endif // !INVLIST_H
