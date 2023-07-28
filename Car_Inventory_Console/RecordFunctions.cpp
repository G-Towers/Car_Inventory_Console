// Implementation of array-based Record functions.

#include "RecordFunctions.h"
#include "Interface.h"

void DisplayErrFile()
{
    ifstream inputFile;
    string line;
    //int errSize = 0;

    // Open input file and test for failure.
    inputFile.open("errors.txt");
    if (!inputFile)
    {
        cout << "Input file failed to open. Quitting program!" << endl;
        system("pause");
        exit(EXIT_FAILURE);
    }

    // Output errors.
    while (getline(inputFile, line, '\0'))
    {
        for (char text : line)
        {
            cout << text;
        }
    }

    // Reset the file stream.
    inputFile.clear();   // Clear the input stream.
    inputFile.seekg(0, inputFile.beg); // Set the position to the beginning of the file.

    // Check for empty file.
    inputFile.seekg(0, ios::end);
    if (inputFile.tellg() == 0) // If empty, print message.
    {
        cout << "The error file is empty." << endl;
    }

    // Close the files.
    inputFile.close();

}

void ReadFile(InvStorage& inv, ErrMsgs& err)
{
    // input file size.
    int inputSize = 0;

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
    while (inputSize < MAX_SIZE && !inputFile.eof())
    {
        // Read each line and assign to strings.
        inputFile >> id >> mod >> quant >> prc;


        // Validate and store valid data.
        if (IDValid(id) && ModelValid(mod) && QuantityValid(quant) && PriceValid(prc) && !IDExists(inv, id))
        {
            // Write entries to record array.
            inv.carRec[inv.carCount].SetID(ToUpper(id));
            inv.carRec[inv.carCount].SetModel(ToUpper(mod));
            inv.carRec[inv.carCount].SetQuantity(stoi(quant));
            inv.carRec[inv.carCount].SetPrice(stof(prc));

            // Assign pointers.
            inv.ptrRec[inv.carCount] = &inv.carRec[inv.carCount];

            inv.carCount++;  // Increment the size of the car array (valid records).
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

            if (IDExists(inv, id, err))
            {
                err.errorMsgs[err.errCount] += err.idExistsErrMsg;
            }

            err.errCount++;  // Count for records with errors.

        }

        inputSize++;    // Increment the input size.
        err.ResetErrStrings();
    }

    // Write to error file.
    WriteErrorFile(err);

    // Check if input file is empty.
    if (inputSize == 0)
    {
        cout << "The input file is empty. Quitting program!" << endl;
        system("pause");
        exit(EXIT_FAILURE);

    }

    // Check to see if size of car array is maxed out.
    if (inv.carCount == MAX_SIZE && !inputFile.eof())
    {
        cout << "\nThe Maximum number of entries have been stored.\n"
            << "Only the first " << MAX_SIZE << " entries can be processed." << endl;

    }

    // Close the files.
    inputFile.close();


}

void RawReadFile(InvStorage& inv)
{
    // input file size.
    int inputSize = 0;

    // Temporary strings.
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

    // Get values from the input file and write to array.
    while (inputSize < MAX_SIZE && !inputFile.eof())
    {
        // Read each line and assign to strings.
        inputFile >> id >> mod >> quant >> prc;

        // Write entries to raw record array.
        inv.rawCarRec[inv.rawCount].SetID(id);
        inv.rawCarRec[inv.rawCount].SetModel(mod);
        inv.rawCarRec[inv.rawCount].SetQuantity(stoi(quant));
        inv.rawCarRec[inv.rawCount].SetPrice(stof(prc));

        inv.rawCount++;  // Increment the size of the raw array.

    }

    inputSize++;    // Increment the input size.

    // Check if input file is empty.
    if (inputSize == 0)
    {
        cout << "The input file is empty. Quitting program!" << endl;
        system("pause");
        exit(EXIT_FAILURE);

    }

    // Check to see if size of array is maxed out.
    if (inv.rawCount == MAX_SIZE && !inputFile.eof())
    {
        cout << "\nThe Maximum number of entries have been stored.\n"
            << "Only the first " << MAX_SIZE << " entries can be processed." << endl;

    }

    // Close the files.
    inputFile.close();


}

void WriteErrorFile(ErrMsgs& err)
{
    // Declare output stream.
    ofstream errorFile;

    // Open error file and test for failure.
    errorFile.open("errors.txt");
    if (!errorFile)
    {
        cout << "Error file failed to open. Quitting program!" << endl;
        errorFile.close();
        system("pause");
        exit(EXIT_FAILURE);
    }

    // write to error file.
    errorFile << err.errorMsgs[0];

    for (int i = 1; i < err.errCount; i++)
    {
        errorFile << "\n" << err.errorMsgs[i];
    }

    // Close the error file.
    errorFile.close();

}

void WriteFile(InvStorage& inv)
{

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
    for (int i = 0; i < inv.rawCount - 1; i++)
    {
        outputFile << inv.rawCarRec[i].GetID() << " " << inv.rawCarRec[i].GetModel() << " " << inv.rawCarRec[i].GetQuantity()
            << " " << inv.rawCarRec[i].GetPrice() << endl;
    }
    outputFile << inv.rawCarRec[inv.rawCount - 1].GetID() << " " << inv.rawCarRec[inv.rawCount - 1].GetModel() << " " << inv.rawCarRec[inv.rawCount - 1].GetQuantity()
        << " " << inv.rawCarRec[inv.rawCount - 1].GetPrice();

    // Close the file.
    outputFile.close();

}

void WriteAppendFile(InvStorage& inv)
{

    // Declare file stream.
    ofstream outputFile;

    // How to append to the end of file------
    // file.open("test.txt", ios::out | ios::app);
    // appending the message to the file
    // file << message << endl;

    // Open file in append mode.
    outputFile.open("records.txt", ios::out | ios::app);

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
    for (int i = 0; i < inv.inputCount; i++)
    {
        outputFile << "\n" << inv.inputRec[i].GetID() << " " << inv.inputRec[i].GetModel() << " " << inv.inputRec[i].GetQuantity()
            << " " << inv.inputRec[i].GetPrice();
    }

    // Close the file.
    outputFile.close();

}
bool IDValid(string id)
{
    bool valid = true;

    // Check ID length.
    if (id.length() < MAX_ID_LENGTH || id.length() > MAX_ID_LENGTH)
    {
        valid = false;
    }

    // Check ID if alpha-numeric.
    for (size_t i = 0; i < id.length(); i++)
    {
        if (!isalnum(id.at(i)))
        {
           valid = false;
           break;
        }
    }

    // Check ID at index 0 and index 1 if alphabetical.
    if (!isalpha(id.at(0)) || !isalpha(id.at(1)))
    {
        valid = false;
    }

    // Check ID at index 0 and index 1 if letters A - F.
    if ((ToUpper(id).at(0) > 'F' || ToUpper(id).at(0) < 'A') || (ToUpper(id).at(1) > 'F' || ToUpper(id).at(1) < 'A'))
    {
        valid = false;
    }


    return valid;
}
bool IDValid(string id, ErrMsgs& err)
{
    bool valid = true;
    
    // Check ID length.
    if (id.length() < MAX_ID_LENGTH || id.length() > MAX_ID_LENGTH)
    {
        err.idErrMsg += " -- ID must be 7 characters long.\n";

        valid = false;
    }
 
    // Check ID if alpha-numeric.
    for (size_t i = 0; i < id.length(); i++)
    {
        if (!isalnum(id.at(i)))
        {
            err.idErrMsg += " -- ID must contain only alpha-numeric characters.\n";
            valid = false;
            break;

        }
    }

    // Check ID at index 0 and index 1 if alphabetical.
    if (!isalpha(id.at(0)) || !isalpha(id.at(1)))
    {
        err.idErrMsg += " -- First 2 characters in ID must be alpha characters.\n";
        valid = false;
    }

    // Check ID at index 0 and index 1 if letters A - F.
    if ((ToUpper(id).at(0) > 'F' || ToUpper(id).at(0) < 'A') || (ToUpper(id).at(1) > 'F' || ToUpper(id).at(1) < 'A'))
    {
        err.idErrMsg += " -- First 2 characters in ID must be letters A - F.\n";
        valid = false;
    }


    return valid;
}

bool ModelValid(string mod)
{
    bool valid = true;

    // Check model if alpha-numeric or underscore(_).
    for (size_t i = 0; i < mod.length(); i++)
    {
        if (!isalnum(mod.at(i)) && (mod.at(i) != '_'))
        {
            valid = false;
            break;
        }
    }

    // Check model at index 0 if alphabetical.
    if (!isalpha(mod.at(0)))
    {
        valid = false;
    }

    return valid;
}

bool ModelValid(string mod, ErrMsgs& err)
{
    bool valid = true;

    // Check model if alpha-numeric or underscore(_).
    for (size_t i = 0; i < mod.length(); i++)
    {
        if (!isalnum(mod.at(i)) && (mod.at(i) != '_'))
        {
            err.mdlErrMsg = " -- Model must contain only alpha-numeric or underscore characters.\n";
            valid = false;
            break;

        }
    }

    // Check model at index 0 if alphabetical.
    if (!isalpha(mod.at(0)))
    {
        err.mdlErrMsg += " -- The first character in model must be an alpha character.\n";
        valid = false;
    }

    return valid;
}

bool QuantityValid(string quant)
{
    int quantity = 0;
    bool valid = true;

    // Check quantity is a number.
    for (size_t i = 0; i < quant.length(); i++)
    {
        if (!isdigit(quant.at(i)) && quant.at(i) != '-')
        {
            valid = false;
            break;
        }

    }

    if (valid)
    {
        // Convert to integer.
        quantity = stoi(quant);

        // Check if quantity is less than 0.
        if (quantity < 0)
        {
            valid = false;
        }
    }

    return valid;
}

bool QuantityValid(string quant, ErrMsgs& err)
{
    int quantity = 0;
    bool valid = true;

    // Check quantity is a number.
    for (size_t i = 0; i < quant.length(); i++)
    {
        if (!isdigit(quant.at(i)) && quant.at(i) != '-')
        {
            err.quantErrMsg = " -- Quantity must contain only numbers.\n";
            valid = false;
            break;

        }
        
    }

    if (valid)
    {
        // Convert to integer.
        quantity = stoi(quant);

        // Check if quantity is less than 0.
        if (quantity < 0)
        {
            err.quantErrMsg += " -- Quantity must be a positve number or 0.\n";
            valid = false;

        }
    }

    return valid;

}

bool PriceValid(string prc)
{
    bool valid = true;

    // Check price length.
    if (prc.length() < MIN_PRICE_LENGTH || prc.length() > MAX_PRICE_LENGTH)
    {
        valid = false;
    }

    // Check price is a number.
    for (size_t i = 0; i < prc.length(); i++)
    {
        if (!isdigit(prc.at(i)) && (prc.at(i) != '.') && (prc.at(i) != '-'))
        {
            valid = false;
            break;

        }

    }

    // Check if decimal is in the correct place.
    if (prc[prc.length() - 3] != '.')
    {
        valid = false;
    }

    if (valid)
    {
        // Check if price is greater than 0. 
        if (stof(prc) < 1)
        {
            valid = false;
        }

    }

    return valid;
}

bool PriceValid(string prc, ErrMsgs& err)
{
    bool valid = true;

    // Check price length.
    if (prc.length() < MIN_PRICE_LENGTH || prc.length() > MAX_PRICE_LENGTH)
    {
        err.prcErrMsg += " -- Price must be at least 4 characters,\n"
              "    and not more than 10 characters long.\n";

        return false;
    }

    // Check price is a number.
    for (size_t i = 0; i < prc.length(); i++)
    {
        if (!isdigit(prc.at(i)) && (prc.at(i) != '.') && (prc.at(i) != '-'))
        {
            err.prcErrMsg += " -- Price must be a number.\n";
            valid = false;
            break;


        }

    }

    // Check if decimal is in the correct place.
    if (prc[prc.length() - 3] != '.')
    {
        err.prcErrMsg += " -- Price must be expressed as a decimal number.\n";
        valid = false;
    }
        
    if (valid)
    {
        // Check if price is greater than 0. 
        if (stof(prc) < 1)
        {
            err.prcErrMsg += " -- Price must be greater than 0.\n";

            valid = false;
        }

    }

    return valid;

}

void Print(const InvStorage& inv)
{

    cout << "Valid records: " << inv.carCount << '\n' << endl;

    cout << setw(23) << "ID" << setw(25) << "Model" << setw(25) << "Quantity" << setw(21) << "$, Price\n"
        << "--------------------------------------------------------------------------------------------------------------" << endl;

    if (inv.carCount == 0)
    {
        cout << "\nNo records to display." << endl;
    }

    else
    {
        // Print the array.
        for (int i = 0; i < inv.carCount; i++)
        {
            cout << ToString(inv.carRec[i]) << endl;
        }
    }

}

void PrintRecord(Record& rec)
{
    cout << "\n" << setw(23) << "ID" << setw(25) << "Model" << setw(25) << "Quantity" << setw(21) << "$, Price\n"
        << "--------------------------------------------------------------------------------------------------------------" << endl;

    cout << ToString(rec) << endl;
}

string ToString(const Record& rec)
{
    stringstream ss;    // Declare a string stream var.

    // Set the decimal point.
    ss.setf(ios::fixed);
    ss.setf(ios::showpoint);
    ss.precision(2);

    ss << setw(11) << ' ' << setw(17) << rec.GetID()
        << setw(15) << ' ' << left << setw(20) << rec.GetModel()
        << setw(5) << ' ' << right << setw(5) << rec.GetQuantity()
        << setw(10) << ' ' << setw(10) << rec.GetPrice();

    return ss.str();
}

string ToLower(string target)
{
    string tempString = target; // Declare a temp string to hold the target value (the size of target).

    for (size_t i = 0; i < target.length(); i++)
    {
        char letter = target[i];    // Declare a char to compare.

        if (letter >= 'A' && letter <= 'Z') // if character is uppercase
        {
            tempString[i] += 'a' - 'A'; // update the character.
        }

    }

    return tempString;
}

string ToUpper(string target)
{
    string tempString = target; // Declare a temp string to hold the target value (the size of target).

    for (size_t i = 0; i < target.length(); i++)
    {
        char letter = target[i];    // Declare a char to compare.

        if (letter >= 'a' && letter <= 'z') // if character is uppercase
        {
            tempString[i] -= 'a' - 'A'; // update the character.
        }

    }

    return tempString;
}

void SearchRec(const InvStorage& inv, RecordArray& searchArr,  string target)
{

    string tempTarget = ToLower(target);    // Temporary target to lowercase string.
    char* char_arr = &tempTarget[0];    // tempTarget converted to char array.
    size_t modelFound = 0;   // To use with find().
    size_t idFound = 0;

    RecordArray linearSrch; // Array for items found from linear search.
    RecordArray partialSrch; // Array for items found from partial search.
    //int linearSize = 0;     // size of linear array.
    //int partialSize = 0;    // size of partial array. 


    // Iterate through the records.
    for (int i = 0; i < inv.carCount; i++)
    {
        // Temporary lowercase strings for ID and model.
        string tempID = ToLower(inv.carRec[i].GetID());
        string tempModel = ToLower(inv.carRec[i].GetModel());


        // Search string tempID, char_arr is the target, start at index 0, search 3 chars.
        idFound = tempID.find(char_arr, 0, 3);
        modelFound = tempModel.find(char_arr, 0, 3);

        // Compare records (linear search) and add to linear search array.
        if ((tempTarget == tempID || tempTarget == tempModel))
        {
            linearSrch.recArr[linearSrch.arrSize].SetRecord(inv.carRec[i]);
            linearSrch.arrSize++;

        }

        // Add results to partial search array.
        else if ((idFound != string::npos || modelFound != string::npos))
        {
            partialSrch.recArr[partialSrch.arrSize].SetRecord(inv.carRec[i]);
            partialSrch.arrSize++;
        }

    }

    // Prioritize linear search results.
    if (linearSrch.arrSize >= 1)
    {
        for (int i = 0; i < linearSrch.arrSize; i++)
        {
            searchArr.recArr[i].SetRecord(linearSrch.recArr[i]);   // Assign results to search array.
            searchArr.arrSize = linearSrch.arrSize;
        }
    }

    // Partial search results if no result from linear search. 
    else
    {
        for (int i = 0; i < partialSrch.arrSize; i++)
        {
            searchArr.recArr[i].SetRecord(partialSrch.recArr[i]);
            searchArr.arrSize = partialSrch.arrSize;
        }
    }

}

int SearchID(const InvStorage& inv, string target)
{
    int index = 0;  // Index of array for linear search.
    string tempTarget = ToLower(target);    // Temporary target to lowercase string.
    Record linearSrch[MAX_SIZE]; // Array for items found from linear search.

    // Iterate through the records.
    for (int i = 0; i < inv.carCount; i++)
    {
        // Temporary lowercase strings for ID.
        string tempID = ToLower(inv.carRec[i].GetID());

        // Compare records (linear search).
        if (tempTarget == tempID)
        {
            linearSrch[index] = inv.carRec[i];

            return index;
        }

        index++;

    }

    return -1;
}

bool IDExists(const InvStorage& inv, string id)
{
    for (size_t i = 0; i < inv.carCount; i++)
    {
        if (ToLower(id) == ToLower(inv.carRec[i].GetID()))
        {
            return true;
        }
    }

    return false;
}

bool IDExists(const InvStorage& inv, string id, ErrMsgs& err)
{
    for (size_t i = 0; i < inv.carCount; i++)
    {
        if (ToLower(id) == ToLower(inv.carRec[i].GetID()))
        {
            err.idExistsErrMsg += "-- The ID is a duplicate.\n";

            return true;
        }
    }

    return false;
}

void PrintSearchResults(const RecordArray& arr)
{
    cout << "\nResults found: " << arr.arrSize << '\n' << endl;
    cout << setw(23) << "ID" << setw(25) << "Model" << setw(25) << "Quantity" << setw(21) << "$, Price\n";
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;

    if (arr.arrSize == 0)
        cout << "\n" << setw(66) << "No result found.\n" << endl;

    else
        // Print the array.
        for (int i = 0; i < arr.arrSize; i++)
        {
            cout << ToString(arr.recArr[i]) << endl;
        }

}

void BubbleSort(Record* pArr[], int size, bool(*cmp)(const Record*, const Record*))
{
    //int swaps = 1;
    bool swapFlag;
    Record* temp;

    for (int i = 0; i < size - 1; i++)	// Traverse the array.
    {
        swapFlag = false;	// Set swapflag to false for each iteration.

        for (int j = 0; j < size - i - 1; j++)
        {
            // Use comparator function here.
            if (cmp(pArr[j], pArr[j + 1]))	// Out of order if this is true.
            {
                // swap code.
                temp = pArr[j + 1];
                pArr[j + 1] = pArr[j];
                pArr[j] = temp;

                swapFlag = true;	// Update the swap flag.

            }
        }
    }
}

void PrintSorted(Record* arr[], const int arrSize)
{
    // Set the decimal point.
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "Valid Records: " << arrSize << '\n' << endl;

    cout << setw(23) << "ID" << setw(25) << "Model" << setw(25) << "Quantity" << setw(21) << "$, Price\n";
    cout << "---------------------------------------------------------------------------------------------" << endl;

    if (arrSize == 0)
    {
        cout << "The input file is empty." << endl;
    }

    for (int i = 0; i < arrSize; i++)
    {
        cout << ToString(*arr[i]) << endl;
    }
}

void PrintAll(const InvStorage& inv)
{
    cout << "\nDisplay All Records --\n" << endl;
    Print(inv); // Print the records.
}

void PrintInvalid(int& err)
{
    cout << "\nDisplay Invalid Records --\n" << endl;
    cout << "Invalid records: " << err << "\n" << endl;
    DisplayErrFile();
}

void Search(const InvStorage& inv)
{
    int searchCount = 0;    // Search object array size.
    string searchStr;   // User search.
    RecordArray searchRec; // Array for items found from search function.

    cout << "\nSearch Records --\n" << endl;
    cout << "Enter a term to search for: ";
    getline(cin, searchStr);
    cout << endl;

    SearchRec(inv, searchRec, searchStr);
    PrintSearchResults(searchRec);

    searchCount = 0;    // Reset the search array.
}







