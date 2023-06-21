// Function Definitions

#include "RecordFunctions.h"

int MenuUserInput()
{
    // For user input.
    string stringInput = "";
    int intInput = 0;

    // Get user input.
    getline(cin, stringInput);

    // Check if nothing is entered.
    while (stringInput == "")
    {
        cout << "\nYou didn't enter anything!\n";
        cout << "\nEnter your selection: ";
        getline(cin, stringInput);
    }

    // Check if too many characters are entered.
    while (stringInput.length() > 2)
    {
        cout << "\nYou entered too many characters!\n";
        cout << "\nEnter your selection: ";
        getline(cin, stringInput);
    }

    // Convert string to integer.
    intInput = atoi(stringInput.c_str());


    return intInput;
}

string YesNoUserInput()
{
    string stringInput;

    // Get user input.
    getline(cin, stringInput);

    // Check if nothing is entered.
    while (stringInput == "")
    {
        cout << "\nYou didn't enter anything!\n";
        cout << "\nEnter your selection: ";
        getline(cin, stringInput);
    }

    // Check if too many characters are entered.
    while (stringInput.length() > 3)
    {
        cout << "\nYou entered too many characters!\n";
        cout << "\nEnter your selection: ";
        getline(cin, stringInput);
    }

    stringInput = ToUpper(stringInput);
    return stringInput;
}


void DisplayMainMenu()
{
    // Display main menu.
    cout << "\n-- Car Inventory -- \n"
        << "\n1. Display Records on file.\n"
        << "2. Display Invalid Records.\n"
        << "3. Search Records.\n"
        << "4. Sort Records.\n"
        << "5. Manage Records.\n"
        << "6. Quit\n" << endl;
    cout << "\nEnter your selection: ";

}

void DisplaySortMenu()
{
    // Display the Sort sub-menu.
    cout << "\n-- Sort Records --\n"
        << "\nSort and Display Records By:\n"
        << "1. ID number.\n"
        << "2. Model.\n"
        << "3. Quantity.\n"
        << "4. Price.\n"
        << "5. Back to previous menu.\n" << endl;
    cout << "\nEnter your selection: ";
}

void DisplayItemMenu()
{
    // Display the item management sub-menu.
    cout << "\n-- Inventory Item Management --\n"
        << "\n1. Enter New Item.\n"
        << "2. Edit Items on Record File.\n"
        << "3. Delete Item from Record File.\n"
        << "4. Display Newly Entered Items.\n"
        << "5. Save Items to Record File.\n"
        << "6. Back to Previous Menu.\n" << endl;
    cout << "\nEnter your selection: ";
}

void DisplayEditItemMenu()
{
    // Display the edit item sub-menu.
    cout << "\n-- Edit Record --\n"
        << "\n1. Edit ID.\n"
        << "2. Edit Model.\n"
        << "3. Edit Quantity.\n"
        << "4. Edit Price.\n"
        << "5. Edit Record.\n"
        << "6. Display Edited Record.\n"
        << "7. Save Edited Record to File.\n"
        << "8. Back to Previous Menu.\n" << endl;
    cout << "\nEnter your selection: ";
}

void DisplayErrFile()
{
    ifstream inputFile;
    string line;
    int errSize = 0;

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

void ReadFile(RecordArray& recArr_in, Record* pArr[], string errMsgs[], int& arrSize, int& errSize,
    string& id_err, string& mod_err, string& quant_err, string& prc_err)
{
    // Initialize array sizes.
    arrSize = 0;
    errSize = 0;

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
    while (arrSize < MAX_SIZE && !inputFile.eof())
    {
        // Read each line and assign to strings.
        inputFile >> id >> mod >> quant >> prc;

        // Validate and store valid data.
        if (IDValid(id, id_err) && ModelValid(mod, mod_err) && QuantityValid(quant, quant_err) && PriceValid(prc, prc_err))
        {
            // Write entries to record array.
            recArr_in.GetRecArr()[arrSize].SetID(ToUpper(id));
            recArr_in.GetRecArr()[arrSize].SetModel(ToUpper(mod));
            recArr_in.GetRecArr()[arrSize].SetQuantity(stoi(quant));
            recArr_in.GetRecArr()[arrSize].SetPrice(stof(prc));

            // Assign pointers.
            pArr[arrSize] = &recArr_in.GetRecArr()[arrSize];

            arrSize++;  // Increment the size of the array.
        }


        else
        {
            // For invalid records, store appropriate error messages in error array.
            errMsgs[errSize] = id + " " + mod + " " + quant + " " + prc + "\n";

            if (!IDValid(id, id_err))
            {
                errMsgs[errSize] += id_err;

            }

            if (!ModelValid(mod, mod_err))
            {
                errMsgs[errSize] += mod_err;
            }

            if (!QuantityValid(quant, quant_err))
            {
                errMsgs[errSize] += quant_err;
            }

            if (!PriceValid(prc, prc_err))
            {
                errMsgs[errSize] += prc_err;
            }

            errSize++;  // Count for records with errors.

        }

    }

    // Write to error file.
    WriteErrorFile(errMsgs, errSize);

    // Check if empty.
    if (arrSize == 0)
    {
        cout << "The input file is empty. Quitting program!" << endl;
        system("pause");
        exit(EXIT_FAILURE);

    }

    // Check to see if size of array is maxed out.
    if (arrSize == MAX_SIZE && !inputFile.eof())
    {
        cout << "\nThe Maximum number of entries have been stored.\n"
            << "Only the first " << MAX_SIZE << " entries can be processed." << endl;

    }

    // Close the files.
    inputFile.close();


}

void RawReadFile(RecordArray& recArr_in, int& arrSize)
{
    // Initialize array sizes.
    arrSize = 0;

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
    while (arrSize < MAX_SIZE && !inputFile.eof())
    {
        // Read each line and assign to strings.
        inputFile >> id >> mod >> quant >> prc;

        // Write entries to record array.
        recArr_in.GetRecArr()[arrSize].SetID(id);
        recArr_in.GetRecArr()[arrSize].SetModel(mod);
        recArr_in.GetRecArr()[arrSize].SetQuantity(stoi(quant));
        recArr_in.GetRecArr()[arrSize].SetPrice(stof(prc));

        arrSize++;  // Increment the size of the array.

    }

    // Check if empty.
    if (arrSize == 0)
    {
        cout << "The input file is empty. Quitting program!" << endl;
        system("pause");
        exit(EXIT_FAILURE);

    }

    // Check to see if size of array is maxed out.
    if (arrSize == MAX_SIZE && !inputFile.eof())
    {
        cout << "\nThe Maximum number of entries have been stored.\n"
            << "Only the first " << MAX_SIZE << " entries can be processed." << endl;

    }

    // Close the files.
    inputFile.close();


}

void WriteErrorFile(string errMsgs[], const int& errSize)
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
    errorFile << errMsgs[0];

    for (int i = 1; i < errSize; i++)
    {
        errorFile << "\n" << errMsgs[i];
    }

    // Close the error file.
    errorFile.close();

}

void WriteFile(RecordArray& recArr_in, const int& arrSize)
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
    for (int i = 0; i < arrSize - 1; i++)
    {
        outputFile << recArr_in.GetRecArr()[i].GetID() << " " << recArr_in.GetRecArr()[i].GetModel() << " " << recArr_in.GetRecArr()[i].GetQuantity()
            << " " << recArr_in.GetRecArr()[i].GetPrice() << endl;
    }
    outputFile << recArr_in.GetRecArr()[arrSize - 1].GetID() << " " << recArr_in.GetRecArr()[arrSize - 1].GetModel() << " " << recArr_in.GetRecArr()[arrSize - 1].GetQuantity()
        << " " << recArr_in.GetRecArr()[arrSize - 1].GetPrice();

    // Close the file.
    outputFile.close();

}

void WriteAppendFile(RecordArray& recArr_in, const int& arrSize)
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
    for (int i = 0; i < arrSize; i++)
    {
        outputFile << "\n" << recArr_in.GetRecArr()[i].GetID() << " " << recArr_in.GetRecArr()[i].GetModel() << " " << recArr_in.GetRecArr()[i].GetQuantity()
            << " " << recArr_in.GetRecArr()[i].GetPrice();
    }

    // Close the file.
    outputFile.close();

}

bool IDValid(string id, string& err)
{
    bool valid = true;
    err = "";   // Initialize the error message.

    // Check ID length.
    if (id.length() < MAX_ID_LENGTH || id.length() > MAX_ID_LENGTH)
    {
        err += " -- ID must be 7 characters long.\n";

        return false;
    }
 
    // Check ID if alpha-numeric.
    for (size_t i = 0; i < id.length(); i++)
    {
        if (!isalnum(id.at(i)))
        {
            err = " -- ID must contain only alpha-numeric characters.\n";
            valid = false;

        }
    }

    // Check ID at index 0 and index 1 if alphabetical.
    if (!isalpha(id.at(0)) || !isalpha(id.at(1)))
    {
        err += " -- First 2 characters in ID must be alpha characters.\n";
        valid = false;
    }

    // Check ID at index 0 and index 1 if letters A - F.
    if ((ToUpper(id).at(0) > 'F' || ToUpper(id).at(0) < 'A') || (ToUpper(id).at(1) > 'F' || ToUpper(id).at(1) < 'A'))
    {
        err += " -- First 2 characters in ID must be letters A - F.\n";
        valid = false;
    }


    return valid;
}

bool ModelValid(string mod, string& err)
{
    bool valid = true;
    err = "";

    // Check model if alpha-numeric or underscore(_).
    for (size_t i = 0; i < mod.length(); i++)
    {
        if (!isalnum(mod.at(i)) && (mod.at(i) != '_'))
        {
            err = " -- Model must contain only alpha-numeric or underscore characters.\n";
            valid = false;

        }
    }

    // Check model at index 0 if alphabetical.
    if (!isalpha(mod.at(0)))
    {
        err += " -- The first character in model must be an alpha character.\n";
        valid = false;
    }

    return valid;
}

bool QuantityValid(string quant, string& err)
{
    int quantity = 0;
    bool valid = true;
    err = "";

    // Check quantity is a number.
    for (size_t i = 0; i < quant.length(); i++)
    {
        if (!isdigit(quant.at(i)) && quant.at(i) != '-')
        {
            err = " -- Quantity must contain only numbers.\n";
            valid = false;

        }
        
    }

    if (valid)
    {
        // Convert to integer.
        quantity = stoi(quant);

        // Check if quantity is less than 0.
        if (quantity < 0)
        {
            err += " -- Quantity must be a positve number or 0.\n";
            valid = false;

        }
    }

    return valid;

}

bool PriceValid(string prc, string& err)
{
    bool valid = true;
    err = "";

    // Check price length.
    if (prc.length() < MIN_PRICE_LENGTH || prc.length() > MAX_PRICE_LENGTH)
    {
        err = " -- Price must be at least 4 characters,\n"
              "    and not more than 10 characters long.\n";

        return false;
    }

    // Check price is a number.
    for (size_t i = 0; i < prc.length(); i++)
    {
        if (!isdigit(prc.at(i)) && (prc.at(i) != '.') && (prc.at(i) != '-'))
        {
            err += " -- Price must be a number.\n";
            valid = false;


        }

    }

    // Check if decimal is in the correct place.
    if (prc[prc.length() - 3] != '.')
    {
        err += " -- Price must be expressed as a decimal number.\n";
        valid = false;
    }
        
    if (valid)
    {
        // Check if price is greater than 0. 
        if (stof(prc) < 1)
        {
            err += " -- Price must be greater than 0.\n";

            valid = false;
        }

    }

    return valid;

}

void Print(const RecordArray& recArr_in, const int& arrSize)
{

    cout << "Valid records: " << arrSize << '\n' << endl;

    cout << setw(23) << "ID" << setw(25) << "Model" << setw(25) << "Quantity" << setw(21) << "$, Price\n"
        << "--------------------------------------------------------------------------------------------------------------" << endl;

    if (arrSize == 0)
    {
        cout << "\nNo records to display." << endl;
    }

    else
    {
        // Print the array.
        for (int i = 0; i < arrSize; i++)
        {
            cout << ToString(recArr_in.GetRecArr()[i]) << endl;
        }
    }

}

void PrintRecord(Record rec)
{
    cout << "\n" << setw(23) << "ID" << setw(25) << "Model" << setw(25) << "Quantity" << setw(21) << "$, Price\n"
        << "--------------------------------------------------------------------------------------------------------------" << endl;

    cout << ToString(rec) << endl;
}

string ToString(Record& rec)
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

void SearchRec(const RecordArray& recArr_in, Record searchArr[], const int& arrSize, int& searchSize, string target)
{

    string tempTarget = ToLower(target);    // Temporary target to lowercase string.
    char* char_arr = &tempTarget[0];    // tempTarget converted to char array.
    size_t modelFound;   // To use with find().
    size_t idFound;

    Record linearSrch[MAX_SIZE]; // Array for items found from linear search.
    Record partialSrch[MAX_SIZE]; // Array for items found from partial search.
    int linearSize = 0;     // size of linear array.
    int partialSize = 0;    // size of partial array. 


    // Iterate through the records.
    for (int i = 0; i < arrSize; i++)
    {
        // Temporary lowercase strings for ID and model.
        string tempID = ToLower(recArr_in.GetRecArr()[i].GetID());
        string tempModel = ToLower(recArr_in.GetRecArr()[i].GetModel());


        // Search string tempID, char_arr is the target, start at index 0, search 3 chars.
        idFound = tempID.find(char_arr, 0, 3);
        modelFound = tempModel.find(char_arr, 0, 3);

        // Compare records (linear search).
        if ((tempTarget == tempID || tempTarget == tempModel))
        {
            linearSrch[linearSize] = recArr_in.GetRecArr()[i];
            linearSize++;

        }

        // Partial search.
        else if ((idFound != string::npos || modelFound != string::npos))
        {
            partialSrch[partialSize] = recArr_in.GetRecArr()[i];
            partialSize++;
        }

    }

    // Prioritize linear search results.
    if (linearSize >= 1)
    {
        for (int i = 0; i < linearSize; i++)
        {
            searchArr[i] = linearSrch[i];   // Assign results to search array.
            searchSize = linearSize;
        }
    }

    // Partial search results if no result from linear search. 
    else
    {
        for (int i = 0; i < partialSize; i++)
        {
            searchArr[i] = partialSrch[i];
            searchSize = partialSize;
        }
    }

}

int SearchID(const RecordArray& recArr_in, const int& arrSize, string target)
{
    int index = 0;  // Index of array for linear search.
    string tempTarget = ToLower(target);    // Temporary target to lowercase string.
    Record linearSrch[MAX_SIZE]; // Array for items found from linear search.

    // Iterate through the records.
    for (int i = 0; i < arrSize; i++)
    {
        // Temporary lowercase strings for ID.
        string tempID = ToLower(recArr_in.GetRecArr()[i].GetID());

        // Compare records (linear search).
        if (tempTarget == tempID)
        {
            linearSrch[index] = recArr_in.GetRecArr()[i];

            return index;
        }

        index++;

    }

    return -1;
}

bool IDExists(const RecordArray& recArr_in, const int& arrSize, string id)
{
    for (size_t i = 0; i < arrSize; i++)
    {
        if (ToLower(id) == ToLower(recArr_in.GetRecArr()[i].GetID()))
        {
            return true;
        }
    }

    return false;
}

void PrintSearchResults(Record arr[], const int& arrSize)
{
    cout << "\nResults found: " << arrSize << '\n' << endl;
    cout << setw(23) << "ID" << setw(25) << "Model" << setw(25) << "Quantity" << setw(21) << "$, Price\n";
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;

    if (arrSize == 0)
        cout << "\n" << setw(66) << "No result found.\n" << endl;

    else
        // Print the array.
        for (int i = 0; i < arrSize; i++)
        {
            cout << ToString(arr[i]) << endl;
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

void SortWrpr(Record* ptrRec[], int& arrSize)
{
    SortChoice sortMenu = SortChoice::SORT_ID;

    do
    {
        DisplaySortMenu();
        int userInput = MenuUserInput();    // user input.
        sortMenu = (SortChoice)userInput; // cast to enum type.

        switch (sortMenu)
        {
        case SortChoice::SORT_ID:
            SortID(ptrRec, arrSize);
            break;
        case SortChoice::SORT_MODEL:
            SortModel(ptrRec, arrSize);
            break;
        case SortChoice::SORT_QUANTITY:
            SortQuantity(ptrRec, arrSize);
            break;
        case SortChoice::SORT_PRICE:
            SortPrice(ptrRec, arrSize);
            break;
        case SortChoice::PREVIOUS_MENU:
            break;
        default:
            SelectionError();
            break;
        }
    } while (sortMenu != SortChoice::PREVIOUS_MENU);

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

void PrintAll(const RecordArray& recArr_in, int& arrSize)
{
    cout << "\nDisplay All Records --\n" << endl;
    Print(recArr_in, arrSize); // Print the records.
}

void PrintInvalid(int& err)
{
    cout << "\nDisplay Invalid Records --\n" << endl;
    cout << "Invalid records: " << err << "\n" << endl;
    DisplayErrFile();
}

void Search(const RecordArray& recArr_in, const int& sizeUsed)
{
    int searchCount = 0;    // Search object array size.
    string searchStr;   // User search.
    Record searchRec[MAX_SIZE]; // Array for items found from search function.

    cout << "\nSearch Records --\n" << endl;
    cout << "Enter a term to search for: ";
    getline(cin, searchStr);
    cout << endl;

    SearchRec(recArr_in, searchRec, sizeUsed, searchCount, searchStr);
    PrintSearchResults(searchRec, searchCount);

    searchCount = 0;    // Reset the search array.
}

void ManageItem(RecordArray& recArr_in, Record* pArr[], RecordArray& inputArr_in, RecordArray& rawArr, string errMsgs[],
                int& arrSize, int& arrSize_in, int& rawSize, int& errSize,
                string& id_err, string& mod_err, string& quant_err, string& prc_err)
{
    Record tempRec;
    ItemChoice ItemMenu = ItemChoice::INPUT_ITEM;

    do
    {
        DisplayItemMenu();
        int userInput = MenuUserInput();

        ItemMenu = (ItemChoice)userInput; // cast to enum type.

        switch (ItemMenu)
        {
        case ItemChoice::INPUT_ITEM:
            tempRec = InputRecord(rawArr, rawSize, id_err, mod_err, quant_err, prc_err);
            if (tempRec.GetID() == "r" || tempRec.GetModel() == "r" || 
                tempRec.GetQuantity() == 114 || tempRec.GetPrice() == 114.0)
            {
                cout << "\nAborted..." << endl;
                break;
            }
            else
            {
                inputArr_in.GetRecArr()[arrSize_in] = tempRec;
                arrSize_in++;
                break;
            }
            
        case ItemChoice::EDIT_ITEM:
            EditRecord(recArr_in, pArr, inputArr_in, rawArr, errMsgs, arrSize, arrSize_in, rawSize,
                        errSize, id_err, mod_err, quant_err, prc_err);
            break;
        case ItemChoice::DELETE_ITEM:
            DeleteRecord(rawArr, rawSize, id_err);
            ReadFile(recArr_in, pArr, errMsgs, arrSize, errSize, id_err,
                    mod_err, quant_err, prc_err);
            break;
        case ItemChoice::PRINT_ITEM:
            PrintRecord(inputArr_in, arrSize_in);
            break;
        case ItemChoice::SAVE_ITEM:
            SaveRecord(inputArr_in, arrSize_in);
            inputArr_in.ResetRecArr();
            arrSize_in = 0;
            ReadFile(recArr_in, pArr, errMsgs, arrSize, errSize, id_err,
                mod_err, quant_err, prc_err);
            break;
        case ItemChoice::PREV_MENU:
            break;
        default:
            SelectionError();
            break;
        }
    } while (ItemMenu != ItemChoice::PREV_MENU);

}

void QuitMsg()
{
    cout << "\nThank you for your time." << endl;
}

void SelectionError()
{
    cout << "\nError! Your selection is invalid." << endl;
    //cin.clear();
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void SortID(Record* ptrArr[], int& arrSize)
{
    cout << "\nSort by ID number --\n" << endl;

    // Bubble sort using lambda expression.
    BubbleSort(ptrArr, arrSize, [](const Record* r1, const Record* r2)
        { return ToLower(r1->GetID()) > ToLower(r2->GetID()); });

    PrintSorted(ptrArr, arrSize);
}

void SortModel(Record* ptrArr[], int& arrSize)
{
    cout << "\nSort by model --\n" << endl;


    BubbleSort(ptrArr, arrSize, [](const Record* r1, const Record* r2)
        { return ToLower(r1->GetModel()) > ToLower(r2->GetModel()); });

    PrintSorted(ptrArr, arrSize);
}

void SortQuantity(Record* ptrArr[], int& arrSize)
{
    cout << "\nSort by quantity --\n" << endl;

    BubbleSort(ptrArr, arrSize, [](const Record* r1, const Record* r2)
        { return r1->GetQuantity() > r2->GetQuantity(); });

    PrintSorted(ptrArr, arrSize);
}

void SortPrice(Record* ptrArr[], int& arrSize)
{
    cout << "\nSort by price --\n" << endl;

    BubbleSort(ptrArr, arrSize, [](const Record* r1, const Record* r2)
        { return r1->GetPrice() > r2->GetPrice(); });

    PrintSorted(ptrArr, arrSize);
}

Record InputRecord(RecordArray& recArr_in, int& arrSize, string& id_err,
                string& mod_err, string& quant_err, string& prc_err)
{
    string id = "", mod = "", quant = "", prc = "";
    Record tempRec; // Temporary Record.

    id = InputID(recArr_in, arrSize, id_err);
    if (id == "r")
    {
        tempRec.SetID(id);
        return tempRec;
    }
    else
        tempRec.SetID(id);

    mod = InputModel(mod_err);
    if (mod == "r")
    {
        tempRec.SetModel(mod);
        return tempRec;
    }
    else    
        tempRec.SetModel(mod);

    quant = InputQuantity(quant_err);
    if (quant == "r")
    {
        int quantR = int(quant[0]);     // Convert string to int.
        tempRec.SetQuantity(quantR);    // Set int to Record object.
        return tempRec;
    }
    else    
        tempRec.SetQuantity(stoi(quant));
 
    prc = InputPrice(prc_err);
    if (prc == "r")
    {
        float prcR = float(prc[0]);
        tempRec.SetPrice(prcR);
        return tempRec;
    }
    else    
        tempRec.SetPrice(stof(prc));


    return tempRec;
        
}

string InputID(RecordArray& recArr_in, int& arrSize, string& id_err)
{
    string id = "";

    // Prompt the user for ID.
    cout << "\nCar ID's are 7 characters long,\n"
        << "The first 2 characters must be letters A - F.\n"
        << "\nEnter a unique ID ( r to return to menu): ";
    getline(cin, id);

    if (id == "r" || id == "R")
        return id;

    // Check if nothing is entered.
    while (id == "")
    {
        cout << "\nYou didn't enter anything!\n";
        cout << "\nEnter ID: ";
        getline(cin, id);

        if (id == "r" || id == "R")
            return id;
    }

    while (!IDValid(id, id_err))
    {
        cout << "\nID invalid...\n"
            << "\n" << id_err << "\n";
        cout << "\nEnter ID: ";
        getline(cin, id);

        if (id == "r" || id == "R")
            return id;

        // Check if nothing is entered again.
        while (id == "")
        {
            cout << "\nYou didn't enter anything!\n";
            cout << "\nEnter ID: ";
            getline(cin, id);

            if (id == "r" || id == "R")
                return id;
        }

        // Check if ID exists.
        while (IDExists(recArr_in, arrSize, id))
        {
            cout << "\nThat ID is already in use." << endl;
            cout << "\nEnter ID: ";
            getline(cin, id);

            if (id == "r" || id == "R")
                return id;

            // Check if nothing is entered again.
            while (id == "")
            {
                cout << "\nYou didn't enter anything!\n";
                cout << "\nEnter ID: ";
                getline(cin, id);

                if (id == "r" || id == "R")
                    return id;
            }

        }

    }

    // Check if ID exists.
    while (IDExists(recArr_in, arrSize, id))
    {
        cout << "\nThat ID is already in use." << endl;
        cout << "\nEnter ID: ";
        getline(cin, id);

        if (id == "r" || id == "R")
            return id;

        // Check if nothing is entered again.
        while (id == "")
        {
            cout << "\nYou didn't enter anything!\n";
            cout << "\nEnter ID: ";
            getline(cin, id);

            if (id == "r" || id == "R")
                return id;
        }

        while (!IDValid(id, id_err))
        {
            cout << "\nID invalid...\n"
                << "\n" << id_err << "\n";
            cout << "\nEnter ID: ";
            getline(cin, id);

            if (id == "r" || id == "R")
                return id;

            // Check if nothing is entered again.
            while (id == "")
            {
                cout << "\nYou didn't enter anything!\n";
                cout << "\nEnter ID: ";
                getline(cin, id);

                if (id == "r" || id == "R")
                    return id;
            }

        }

    }

    return id;
}

string InputModel(string& mod_err)
{
    string mod;

    // Prompt the user for Model.
    cout << "\nModel Names must be alpha-numeric and may contain underscores ( _ ),\n"
        << "However, the model name must start with an alpha character and cannot\n"
        << "have blank spaces.\n"
        << "\nEnter Model: ";
    getline(cin, mod);

    if (mod == "r" || mod == "R")
        return mod;

    // Check if nothing is entered.
    while (mod == "")
    {
        cout << "\nYou didn't enter anything!\n";
        cout << "\nEnter Model: ";
        getline(cin, mod);

        if (mod == "r" || mod == "R")
            return mod;
    }

    while (!ModelValid(mod, mod_err))
    {
        cout << "\nModel invalid...\n"
            << "\n" << mod_err << "\n";
        cout << "\nEnter Model: ";
        getline(cin, mod);

        if (mod == "r" || mod == "R")
            return mod;

        // Check if nothing is entered again.
        while (mod == "")
        {
            cout << "\nYou didn't enter anything!\n";
            cout << "\nEnter Model: ";
            getline(cin, mod);

            if (mod == "r" || mod == "R")
                return mod;
        }
    }

    return mod;
}

string InputQuantity(string& quant_err)
{
    string quant;

    // Prompt user for quantity.
    cout << "\nEnter quantity of items: ";
    getline(cin, quant);

    if (quant == "r" || quant == "R")
        return quant;

    // Check if nothing is entered.
    while (quant == "")
    {
        cout << "\nYou didn't enter anything!\n";
        cout << "\nEnter Quantity: ";
        getline(cin, quant);

        if (quant == "r" || quant == "R")
            return quant;
    }

    while (!QuantityValid(quant, quant_err))
    {
        cout << "\nQuantity invalid...\n"
            << "\n" << quant_err << "\n";
        cout << "\nEnter Quantity: ";
        getline(cin, quant);

        if (quant == "r" || quant == "R")
            return quant;

        // Check if nothing is entered again.
        while (quant == "")
        {
            cout << "\nYou didn't enter anything!\n";
            cout << "\nEnter Quantity: ";
            getline(cin, quant);

            if (quant == "r" || quant == "R")
                return quant;
        }
    }

    return quant;
}

string InputPrice(string& prc_err)
{
    string prc;

    // Prompt user for price.
    cout << "\nEnter price of item: ";
    getline(cin, prc);

    if (prc == "r" || prc == "R")
        return prc;

    // Check if nothing is entered.
    while (prc == "")
    {
        cout << "\nYou didn't enter anything!\n";
        cout << "\nEnter Price: ";
        getline(cin, prc);

        if (prc == "r" || prc == "R")
            return prc;
    }

    while (!PriceValid(prc, prc_err))
    {
        cout << "\nPrice invalid...\n"
            << "\n" << prc_err << "\n";
        cout << "\nEnter Price: ";
        getline(cin, prc);

        if (prc == "r" || prc == "R")
            return prc;

        // Check if nothing is entered again.
        while (prc == "")
        {
            cout << "\nYou didn't enter anything!\n";
            cout << "\nEnter Price: ";
            getline(cin, prc);

            if (prc == "r" || prc == "R")
                return prc;
        }
    }

    return prc;
}

void EditRecord(RecordArray& recArr_in, Record* pArr[], RecordArray& inputArr_in, RecordArray& rawArr_in, string errMsgs[],
            int& arrSize, int& arrSize_in, int& rawSize, int& errSize, string& id_err, string& mod_err,
            string& quant_err, string& prc_err)
{
    string id, mod, quant, prc; // Store edited input.
    Record tempRec; // Temporary Record.

    string editID;  // Search ID to locate record.
    string recResp; //  User response to edit record.
    string idEdit;

    cout << "\nEnter ID of record to edit: ";
    getline(cin, editID);

    // Check if nothing is entered.
    while (editID == "")
    {
        cout << "\nYou didn't enter anything!\n";
        cout << "\nEnter ID: ";
        getline(cin, editID);
    }

    // Search for the ID.
    int index = SearchID(rawArr_in, rawSize, editID);

    if (index == -1)
    {
        cout << "\nRecord not Found." << endl;
    }

    else
    {
        cout << "\nRecord found: " << rawArr_in.GetRecArr()[index].GetID() << " -- "
            << rawArr_in.GetRecArr()[index].GetModel() << " -- " << rawArr_in.GetRecArr()[index].GetQuantity() << " -- "
            << rawArr_in.GetRecArr()[index].GetPrice() << "\n"
            << "Index: " << index << endl;

        cout << "\nEdit this record? (y/n):";
        recResp = YesNoUserInput();

        if (recResp == "Y" || recResp == "YES")
        {
            int editInput;   // user input for sub menu.
            EditChoice editMenu = EditChoice::EDIT_ID;   // Initialize.

            // Store temporary record.
            tempRec.SetID(rawArr_in.GetRecArr()[index].GetID());
            tempRec.SetModel(rawArr_in.GetRecArr()[index].GetModel());
            tempRec.SetQuantity(rawArr_in.GetRecArr()[index].GetQuantity());
            tempRec.SetPrice(rawArr_in.GetRecArr()[index].GetPrice());

            do
            {
                DisplayEditItemMenu();
                editInput = MenuUserInput();

                editMenu = (EditChoice)editInput; // cast to enum type.

                switch (editMenu)
                {
                case EditChoice::EDIT_ID:
                    idEdit = InputID(rawArr_in, rawSize, id_err);
                    if (idEdit == ToLower("r"))
                        break;
                    else
                    {
                        tempRec.SetID(idEdit);
                        cout << "\nID successfully updated." << endl;
                    }                       
                    break;
                case EditChoice::EDIT_MODEL:
                    tempRec.SetModel(InputModel(mod_err));
                    break;
                case EditChoice::EDIT_QUANTITY:
                    tempRec.SetQuantity(stoi(InputQuantity(quant_err)));
                    break;
                case EditChoice::EDIT_PRICE:
                    tempRec.SetPrice(stof(InputPrice(prc_err)));
                    break;
                case EditChoice::EDIT_RECORD:
                    tempRec = InputRecord(rawArr_in, rawSize, id_err, mod_err, 
                                        quant_err, prc_err);
                    break;
                case EditChoice::DISPLAY_RECORD:
                    PrintRecord(tempRec);
                    break;
                case EditChoice::SAVE_RECORD:
                    rawArr_in.GetRecArr()[index] = tempRec;
                    WriteFile(rawArr_in, rawSize);
                    ReadFile(recArr_in, pArr, errMsgs, arrSize, errSize, id_err,
                        mod_err, quant_err, prc_err);
                    cout << "\nRecord replaced." << endl;
                    break;
                case EditChoice::BACK_PREV:
                    break;
                default:
                    SelectionError();
                    break;
                }
            } while (editMenu != EditChoice::BACK_PREV);

            
            
        }
    }

    
}

void DeleteRecord(RecordArray& recArr_in, int& arrSize, string& id_err)
{
    string delID;   // ID to delete.
    string resp;  // User response. 

    cout << "\nEnter ID for record to delete: ";
    getline(cin, delID);

    // Check if nothing is entered.
    while (delID == "")
    {
        cout << "\nYou didn't enter anything!\n";
        cout << "\nEnter ID: ";
        getline(cin, delID);
    }

    while (!IDValid(delID, id_err))
    {
        cout << "\nID invalid...\n"
            << "\n" << id_err << "\n";
        cout << "\nEnter ID: ";
        getline(cin, delID);

        // Check if nothing is entered again.
        while (delID == "")
        {
            cout << "\nYou didn't enter anything!\n";
            cout << "\nEnter ID: ";
            getline(cin, delID);
        }

    }

    int index = SearchID(recArr_in, arrSize, delID);

    if (index == -1)
    {
        cout << "\nRecord not Found." << endl;
    }

    else
    {
        // Display record if found.
        cout << "\nRecord found: " << recArr_in.GetRecArr()[index].GetID() << " "
            << recArr_in.GetRecArr()[index].GetModel() << " " << recArr_in.GetRecArr()[index].GetQuantity() << " "
            << recArr_in.GetRecArr()[index].GetPrice() << "\n"
            << "Index: " << index << endl;

        cout << "\nDelete record on file? (y/n): ";
        resp = YesNoUserInput();


        if (resp == "Y" || resp == "YES")
        {
            for (int i = index; i < arrSize - 1; i++)
            {
                recArr_in.GetRecArr()[i] = recArr_in.GetRecArr()[i + 1];
            }
            arrSize--;

            WriteFile(recArr_in, arrSize);
            cout << "\nRecord deleted." << endl;

        }
    }

}

void PrintRecord(RecordArray& recArr_in, int& arrSize)
{
    cout << "\nDisplay Entered Records --\n" << endl;
    Print(recArr_in, arrSize); // Print records to screen.
}

void SaveRecord(RecordArray& recArr_in, int& arrSize)
{
    string resp;

    cout << "\nSave to record file? (y/n): ";
    resp = YesNoUserInput();

    if (resp == "Y" || resp == "YES")
    {
        WriteAppendFile(recArr_in, arrSize);
        cout << "\nRecord saved." << endl;
    }
}
