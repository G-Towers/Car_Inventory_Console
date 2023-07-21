#ifndef NODE_H
#define NODE_H

#include "Record.h"

// A struct for each node in the list.
class Node
{

public:
	int key = 1;	// A unique value to identify and refer (access) the node.
	Record rec;		// The data stored in that node.
	Node* next = nullptr;	// A pointer of type Node that points to the next Node. Points to an object/class
							// of Node type only.
};

#endif // !NODE_H
