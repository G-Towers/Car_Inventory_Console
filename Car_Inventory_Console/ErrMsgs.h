
#ifndef ERRMSGS_H
#define ERRMSGS_H

#include "RecordArray.h"
#include <string>

using namespace std;

class ErrMsgs
{
public:
    ErrMsgs() { SetErrMsgs("", "", "", "", 0, ""); }

    void SetErrMsgs(string id, string mdl, string quant, string prc, int err, string errMsg)
    {
        idErrMsg = id;
        mdlErrMsg = mdl;
        quantErrMsg = quant;
        prcErrMsg = prc;
        errCount = err;

        for (int i = 0; i < MAX_ERR_MSG; i++)
        {
            errorMsgs[i] = errMsg;
        }

    }

public:
    // Error message strings.
    string idErrMsg;
    string mdlErrMsg;
    string quantErrMsg;
    string prcErrMsg;

    int errCount;    // How many records with errors in file.

    // Array of error messages.
    string errorMsgs[MAX_ERR_MSG];

    
};

#endif // !ERRMSGS_H