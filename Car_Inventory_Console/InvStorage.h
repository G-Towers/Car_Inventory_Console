
#ifndef INVSTORAGE_H
#define INVSTORAGE_H

#include "RecordArray.h"



class InvStorage
{
public:
    InvStorage()
    {
        carRec = new Record[MAX_SIZE];
        rawCarRec = new Record[MAX_SIZE];
        inputRec = new Record[MAX_INPUT_SIZE];
    }

    ~InvStorage()
    {
        delete[] carRec;
        carRec = nullptr;

        delete[] rawCarRec;
        rawCarRec = nullptr;

        delete[] inputRec;
        inputRec = nullptr;

        // Pointer array to nullptr.
        for (int i = 0; i < MAX_SIZE; i++)
        {
            ptrRec[i] = nullptr;
        }
    }

    void ResetCarRec()
    {
        delete[] carRec;
        carRec = new Record[MAX_SIZE];
        carCount = 0;
    }

    void ResetRawCarRec()
    {
        delete[] rawCarRec;
        rawCarRec = new Record[MAX_SIZE];
        rawCount = 0;
    }

    void ResetInputRec()
    {
        delete[] inputRec;
        inputRec = new Record[MAX_SIZE];
        inputCount = 0;
    }

public:
    // Declare dynamic arrays.
    Record* carRec;  // Main record array of valid automobiles (only valid records).
                        // Primarilly used for displaying valid records to the user.

    Record* rawCarRec;   // Array for unaltered record file (everthing on record file).
    Record* inputRec;  // Temp record array for the input of new records via the Manage Records Menu.
    Record* ptrRec[MAX_SIZE] = {nullptr};   // Parallel array of pointers (used for sorting).

    int carCount = 0;  // Array size for carRec (valid records).
    int rawCount = 0;   // Size for raw array (all entries on file).
    int inputCount = 0; // Array size for inputRec (used for inputing records in Manage Records).
};

#endif // !INVSTORAGE_H