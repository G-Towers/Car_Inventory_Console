// #pragma once

#ifndef RECORDARRAY_H
#define RECORDARRAY_H

#include "Record.h"

class RecordArray
{
public:
	RecordArray()
	{
		rec = new Record[MAX_SIZE];
	}

	~RecordArray()
	{
		delete [] rec;
	}

private:
	Record* rec;
	

};

#endif // !RECORDARRAY_H
