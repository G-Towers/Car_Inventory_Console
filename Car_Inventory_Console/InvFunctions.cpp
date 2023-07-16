// Implementation of Linked List Functions.

#include "InvFunctions.h"
#include "RecordFunctions.h"

string ToStringKey(const Node* nod)
{
    stringstream ss;    // Declare a string stream var.

    // Set the key to at least 2 digits.
    ss << "(" << setfill('0') << setw(2) << nod->GetKey() << setw(0) << setfill(' ') << ")";

    // Set the decimal point.
    ss.setf(ios::fixed);
    ss.setf(ios::showpoint);
    ss.precision(2);

    ss << setw(10) << ' ' << setw(14) << nod->GetRecord().GetID()
        << setw(15) << ' ' << left << setw(20) << nod->GetRecord().GetModel()
        << setw(5) << ' ' << right << setw(5) << nod->GetRecord().GetQuantity()
        << setw(10) << ' ' << setw(10) << nod->GetRecord().GetPrice();

    return ss.str();

}

void ReadFileList(InvList& lstItem, ErrMsgs& err)
{
    int inputSize = 0;  // Input file size.
    int key = 1;

    Record rec;
    Node* fileNode = nullptr;

    // Temporary string used for validation.
    string id = "",
        mod = "",
        quant = "",
        prc = "";

    // Declare file streams.
    ifstream inputFile;

    // Open input file and test for failure.
    inputFile.open("records.txt");
    if (!inputFile)
    {
        cout << "Input file failed to open. Quitting program!" << endl;
        system("pause");
        exit(EXIT_FAILURE);
    }

    // Get values from the input file, validate, and write to array.
    while (!inputFile.eof())
    {
        // Allocate dynamic memory.
        // Create a new node for every iteration.
        fileNode = new Node();


        // Read each line and assign to strings.
        inputFile >> id >> mod >> quant >> prc;

        // Validate and store valid data.
        if (IDValid(id) && ModelValid(mod) && QuantityValid(quant) && PriceValid(prc))
        {

            // Set to record.
            rec.SetID(ToUpper(id));
            rec.SetModel(ToUpper(mod));
            rec.SetQuantity(stoi(quant));
            rec.SetPrice(stof(prc));

            // Store in the linked list.
            fileNode->SetKey(key);
            fileNode->SetRecord(rec);
            lstItem.AppendNode(fileNode);
            lstItem++;
            key++;

        }

        else
        {
            // For invalid records, store appropriate error messages in error object.
            err.errorMsgs[err.errCount] = id + " " + mod + " " + quant + " " + prc + "\n";

            if (!IDValid(id, err))
            {
                err.errorMsgs[err.errCount] += err.idErrMsg;
            }

            if (!ModelValid(mod, err))
            {
                err.errorMsgs[err.errCount] += err.mdlErrMsg;
            }

            if (!QuantityValid(quant, err))
            {
                err.errorMsgs[err.errCount] += err.quantErrMsg;
            }

            if (!PriceValid(prc, err))
            {
                err.errorMsgs[err.errCount] += err.prcErrMsg;
            }

            err.errCount++;  // Count for records with errors.

        }
        inputSize++;    // Increment the input size.
        err.ResetErrStrings();


    }

    //  Write to error file.
    WriteErrorFile(err);

    // Check if list is empty.
    if (lstItem.GetHead() == nullptr)
    {
        cout << "The input file is empty. Quitting program!" << endl;
        system("pause");
        exit(EXIT_FAILURE);

    }



    // Close the files.
    inputFile.close();


}

void WriteFileList(InvList lstItem)
{
    Node* tmp = lstItem.GetHead();

    // Declare file stream.
    ofstream outputFile;

    // Open file.
    outputFile.open("records.txt");

    // Test for file opening failure.
    if (!outputFile)
    {
        cout << "Output file failed to open.\n";
        system("pause");
        exit(EXIT_FAILURE);
    }

    // Set the decimal point.
    outputFile.setf(ios::fixed);
    outputFile.setf(ios::showpoint);
    outputFile.precision(2);

    // Write to the file.
    for (int i = 0; i < lstItem.GetSize() - 1; i++)
    {
        outputFile << tmp->GetRecord().GetID() << " "
            << tmp->GetRecord().GetModel() << " "
            << tmp->GetRecord().GetQuantity() << " "
            << tmp->GetRecord().GetPrice()
            << endl;

        tmp = tmp->GetNext();
    }

    outputFile << tmp->GetRecord().GetID() << " "
        << tmp->GetRecord().GetModel() << " "
        << tmp->GetRecord().GetQuantity() << " "
        << tmp->GetRecord().GetPrice();


    // Close the file.
    outputFile.close();

}

void Search(InvList& lstItem)
{
    string searchStr;
    InvList searchLst; // List for items found.

    cout << "\nSearch Records --\n" << endl;
    cout << "Enter a term to search for: ";
    getline(cin, searchStr);
    cout << endl;

    SearchList(lstItem, searchLst, searchStr);
    PrintSearchResultsList(searchLst);

}

void SearchList(InvList& lstItem, InvList& searchList, string target)
{
    string tempTarget = ToLower(target);    // Temporary target to lowercase string.
    char* char_arr = &tempTarget[0];    // tempTarget converted to char array.
    size_t modelFound;   // To use with find().
    size_t idFound;

    // List for search results
    InvList linearLst; // List for items found from linear search.
    InvList partialLst; // List for items found from partial search.


    Node* temp = nullptr;   // Used for search Lists.
    Node* ptr = lstItem.GetHead();	// Local pointer for this function only.
    // Used in pointing to nodes in a list (while traversing the list).


    // Traverse the list.
    while (ptr != nullptr)	// Iterate through the entire list.
    {
        // Allocate memory for temp.
        temp = new Node();

        // Temporary lowercase strings for ID and model.
        string tempID = ToLower(ptr->GetRecord().GetID());
        string tempModel = ToLower(ptr->GetRecord().GetModel());

        // Search string tempID, char_arr is the target, start at index 0, search 3 chars.
        idFound = tempID.find(char_arr, 0, 3);
        modelFound = tempModel.find(char_arr, 0, 3);

        // Check each node for the target value (Linear Search).
        if (tempID == tempTarget || tempModel == tempTarget)
        {
            //temp = ptr;	// if the target being passed is in the list
            // temp will be assigned the address of that node.
            temp->SetKey(ptr->GetKey());
            temp->SetRecord(ptr->GetRecord());
            linearLst.AppendNode(temp);
            linearLst++;
        }

        // Partial search.
        else if ((idFound != string::npos || modelFound != string::npos))
        {
            //cout << "Key: " << ptr->GetKey() << "  Record: " << ptr->GetRecord() << endl;
            temp->SetKey(ptr->GetKey());
            temp->SetRecord(ptr->GetRecord());
            partialLst.AppendNode(temp);
            partialLst++;
        }

        ptr = ptr->GetNext(); // Store the address of the next node.
        // This is how the traversal is incremented from node to node.
    }

    // Prioritize linear search results.
    if (linearLst.GetSize() >= 1)
        searchList = linearLst;

    // Partial search results if no result from linear search. 
    else
        searchList = partialLst;


}

int SearchIDList(const InvList& lstItem, string target)
{
    int key = 0;  // Index of array for linear search.
    string tempTarget = ToLower(target);    // Temporary target to lowercase string.
    Node* tmpPtr = lstItem.GetHead();  // Local pointer for this function only.
    // used to assign the node head is pointing to (while traversing the list).

// Iterate through the list.
    while (tmpPtr != nullptr)
    {
        // Temporary lowercase strings for ID.
        string tempID = ToLower(tmpPtr->GetRecord().GetID());

        // Compare records (linear search).
        if (tempID == tempTarget)
        {
            key = tmpPtr->GetKey();
            return key;
        }

        tmpPtr = tmpPtr->GetNext(); // Traverse.

    }

    return -1;
}

bool IDExistsList(const InvList& lstItem, const int& list_size, string id)
{
    //Node* tmp = nullptr; 
    Node* tmpPtr = lstItem.GetHead();  // Local pointer for this function only.
    // used to assign the node head is pointing to (while traversing the list).

    while (tmpPtr != nullptr)   // Iterate through the list.
    {
        if (tmpPtr->GetRecord().GetID() == id)
        {
            return true;
        }

        tmpPtr = tmpPtr->GetNext(); // Store the address of the next node.
        // This is how the traversal is incremented from node to node.
    }

    return false;
}

// Prints the list
void PrintList(const InvList& list)
{
    if (list.GetHead() == nullptr)
    {
        cout << "\nThe list is empty." << endl;
    }

    else
    {
        cout << "\nList Items --\n" << endl;
        Node* temp = list.GetHead();

        cout << "Key" << setw(20) << "ID" << setw(25) << "Model" << setw(25) << "Quantity" << setw(21) << "$, Price\n"
            << "--------------------------------------------------------------------------------------------------------------" << endl;

        while (temp != nullptr)
        {
            cout << ToStringKey(temp) << endl;
            temp = temp->GetNext();

        }

        cout << endl;

    }
}

void PrintSearchResultsList(const InvList& list)
{
    if (list.GetHead() == nullptr)
    {
        cout << "\nNo result found." << endl;
    }

    else
    {
        Node* temp = list.GetHead();

        cout << "\nResults found: " << list.GetSize() << '\n' << endl;

        cout << "Key" << setw(20) << "ID" << setw(25) << "Model" << setw(25) << "Quantity" << setw(21) << "$, Price\n"
            << "--------------------------------------------------------------------------------------------------------------" << endl;

        while (temp != nullptr)
        {
            cout << ToStringKey(temp) << endl;
            temp = temp->GetNext();

        }

        cout << endl;
    }


}

Node* SwapPtr(Node* swpPtr1, Node* swpPtr2)
{
    Node* tmp = swpPtr2->GetNext();
    swpPtr2->SetNext(swpPtr1);
    swpPtr1->SetNext(tmp);

    return swpPtr2;

}

void BubbleSortList(Node** head_in, int list_size, bool(*cmp)(const Node*, const Node*))
{
    Node** tmpPtr = nullptr;
    Node* ptr1 = nullptr;
    Node* ptr2 = nullptr;
    bool swapped = false;

    for (int i = 0; i <= list_size; i++)
    {
        tmpPtr = head_in;
        swapped = false;    // Reset the swap flag.

        for (int j = 0; j < list_size - i - 1; j++)
        {
            ptr1 = *tmpPtr;
            ptr2 = ptr1->GetNext();

            if (cmp(ptr1, ptr2))
            {
                *tmpPtr = SwapPtr(ptr1, ptr2);
                swapped = true;
            }

            tmpPtr = &(*tmpPtr)->next;  // How to do this if Node* private?

        }

        if (!swapped)
            break;

    }


}