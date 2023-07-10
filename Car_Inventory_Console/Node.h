#ifndef NODE_H
#define NODE_H

#include "Record.h"

// A class for each node in the list.
class Node
{
public:

	// Default constructors.
	Node()
	{
		key = 0;
		rec;
		next = nullptr;
	}

	// Constructor with parameters.
	Node(int key, Record rec)
	{
		this->key = key;
		this->rec = rec;
		next = nullptr;
	}

	// Access to members.

	void SetNode(int key, Record rec, Node* next)
	{
		this->key = key;
		this->rec = rec;
		this->next = next;
	}

	void SetKey(int key) { this->key = key; }
	void SetRecord(Record rec) { this->rec = rec; }
	void SetNext(Node* next) { this->next = next; }

	int GetKey() const { return key; }
	Record GetRecord() const { return rec; }
	Node* GetNext() const { return next; }




private:
	int key;	// A unique key to identify and refer (access) the node.
	Record rec;	// The data stored in that node.

public:
	Node* next;	// A pointer of type Node that points to the next Node. Points to an object/class
				// of Node type only.

};

#endif // !NODE_H
