
#ifndef ERRMSGS_H
#define ERRMSGS_H

#include "RecordArray.h"
#include <string>

using namespace std;

class ErrMsgs
{
public:
    ErrMsgs()
    {
        errorMsgs = new string[MAX_ERR_MSG];
        //SetErrMsgs("", "", "", "");
    }

    ~ErrMsgs()
    {
        delete[] errorMsgs;
        errorMsgs = nullptr;
    }

    // { SetErrMsgs("", "", "", "", 0); }

    void SetErrMsgs(string id, string mdl, string quant, string prc)
    {
        idErrMsg = id;
        mdlErrMsg = mdl;
        quantErrMsg = quant;
        prcErrMsg = prc;
        //errCount = err;


    }

    void ResetErrArr()
    {
        delete[] errorMsgs;
        errorMsgs = new string[MAX_ERR_MSG];
        errCount = 0;
    }

    void ResetErrStrings()
    {
        SetErrMsgs("", "", "", "");
    }

public:
    // Error message strings.
    string idErrMsg = "";
    string mdlErrMsg  = "";
    string quantErrMsg = "";
    string prcErrMsg = "";

    int errCount = 0;    // How many records with errors in file.

    // Array of error messages.
    string* errorMsgs;

    
};

#endif // !ERRMSGS_H