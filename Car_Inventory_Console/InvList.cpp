// Implementation of Linked List Functions.

#include "InvList.h"

// Checks if a Node exists using key value.
// Manages whether key value is duplicated or not (key must be unique to each node).
// The function will either return the address of an existing node if key is found
// or will return nullptr if not found.
Node* InvList::NodeExists(int key)	// Pass key value.
{
	Node* temp = nullptr;
	Node* ptr = head;	// Local pointer for this function only.
	// used to assign the node head is pointing to (while traversing the list).

// Traverse the list using address's and ptr pointer.
	while (ptr != nullptr)	// Iterate through the entire list.
	{
		if (ptr->key == key)	// Check each node for the key value.
		{
			temp = ptr;	// if the key being passed is in the list
			// temp will be assigned the address of that node.
		}

		ptr = ptr->next; // Store the address of the next node.
		// This is how the traversal is incremented from node to node.
	}

	return temp;
}

// Appends a Node to the list (end of list).
void InvList::AppendNode(Node* nod)	// Passes the nodes address by pointer.
{
	Node* tempNode = new Node;	// Allocate on the heap.
	tempNode = nod;

	// Check to see if the key value is in the list.
	if (NodeExists(tempNode->key) != nullptr)
	{
		std::cout << "Node already exists with key value of " << tempNode->key
			<< ". Please append with a different key value." << endl;
	}

	else
	{
		// Head will be pointing to nullptr when the list is empty.
		if (head == nullptr)
		{
			head = tempNode;	// assign the address of n to head.
			//cout << "Node Appended." << endl;
		}

		// When there are values in the list and head is pointing to a node in the list.
		else
		{
			Node* ptr = head;	// Pointer used for iterating through the list (initialised to the beginning of the list).

			// Traverse to the end of the list.
			while (ptr->next != nullptr)
			{
				ptr = ptr->next;	// ptr points to the next node
				// until nullptr is encountered.
			}

			ptr->next = tempNode;	// Assign the address of its next pointer to the new node.
			//cout << "Node Appended." << endl;
		}
	}
}

// Prepends a Node to the list (Attaches at start).
void InvList::PrependNode(Node* nod)
{
	Node* tempNode = new Node;
	tempNode = nod;

	// Check to see if the key value is in the list.
	if (NodeExists(tempNode->key) != nullptr)
	{
		cout << "Node already exists with key value of " << tempNode->key
			<< ". Please prepend with a different key value." << endl;
	}

	//  Attach the node to the beginning of the list.
	else
	{
		tempNode->next = head;	// Since head is already pointing to the first node, assign head to n's next.
		head = tempNode;	// Then head points to the new node.
		cout << "Node Prepended." << endl;
	}
}

// Inserts a node at a specified location (after specified key)
void InvList::InsertNodeAfter(int key, Node* nod)
{
	Node* tempNode = new Node;
	tempNode = nod;

	// Create a Node ptr to access the key value if it exists (acts like a temp pointer).
	Node* ptr = NodeExists(key);	// Search the list for a particular key to insert after.

	// If ptr equals nullptr, key value does not exist.
	if (ptr == nullptr)
	{
		cout << "No node exists with key value of " << key << endl;
	}

	// if the key value exists
	else
	{
		// Make sure the key value of the new node is unique.
		if (NodeExists(tempNode->key) != nullptr)
		{
			cout << "Node already exists with key value of " << tempNode->key
				<< ". Please prepend with a different key value." << endl;
		}

		// Link the new node.
		else
		{
			// Linking must be in order because ptr's next address is overwritten.
			// Remember, ptr is dereferncing so it's like your assigning to the nodes themselves.
			tempNode->next = ptr->next;	// Assign ptr's next pointer to the new nodes next pointer (new nodes next pointer points to the next node).
			ptr->next = tempNode;	// Link the previous node to the new node using ptr.
			cout << "Node Inserted." << endl;
		}
	}
}

// Deletes a Node by key
void InvList::DeleteNodeByKey(int key)
{
	// Check if list is populated.
	if (head == nullptr)
	{
		cout << "List is empty. Cannot delete." << endl;
	}

	// 
	else if (head != nullptr)
	{
		// if node to delete is the head node
		if (head->key == key)
		{
			head = head->next;	// point the head to the node after (unlinking it).
			cout << "Item " << key << " Deleted." << endl;	// Node is not deleted, it's simply unlinked.
		}

		// Delete any other node other than head.
		else
		{
			Node* temp = nullptr;	// To store the node if/when found.
			Node* prevPtr = head;	// Stores the current pointer initialized to the beginning of the list.
			Node* currentPtr = head->next;	// Stores the current pointer to search the list.

			// traverse the list to search for key to delete.
			while (currentPtr != nullptr)
			{
				if (currentPtr->key == key)
				{
					temp = currentPtr;	// When key is found, assign to temp.
					currentPtr = nullptr;	// set to nullptr to exit loop.
				}
				else
				{
					prevPtr = prevPtr->next;	// Increment the prevPtr.
					currentPtr = currentPtr->next;	// Increment the currentPtr.
				}
			}

			if (temp != nullptr)	// if key is found (temp will stay null if nothing found).
			{
				prevPtr->next = temp->next;	// Previous pointer points to node after temp (deleting the node).
				cout << "Item " << key << " Deleted." << endl;
			}

			// if key is not found.
			else
			{
				cout << "Item " << key << " doesn't exist." << endl;
			}
		}
	}
}

// Update the node with a new data value.
// Accesses the node by key value and updates data.
void InvList::UpdateNodeByKey(int key, Record rec)
{
	Node* ptr = NodeExists(key);	// Check if key exists and assign address to ptr (returns null if not).

	if (ptr != nullptr)	// if key exists
	{
		ptr->rec = rec;	// update data value.
		cout << "Node data updated successfully." << endl;
	}

	// if not
	else
	{
		cout << "Node doesn't exist with key value of " << key << endl;
	}
}

Node* InvList:: GetCurrentNode(Node* head, int key) 
{
	Node* current = head;
	int count = 0;

	while (current != nullptr) 
	{
		if (count == key)
			return current;

		count++;
		current = current->next;
	}
	return nullptr;
}

