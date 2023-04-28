// #pragma once

#ifndef RECORDARRAY_H
#define RECORDARRAY_H

#include "Record.h"

class RecordArray
{
public:
	RecordArray()
	{
		recArr = new Record[MAX_SIZE];
		
	}

	~RecordArray()
	{
		delete [] recArr;
		recArr = nullptr;
	}

	// Member access
	Record* GetRecArr() const { return recArr; }
	//void SetRecArr(string id, string mod, int quant, float pr);

private:
	Record* recArr;
	

};

#endif // !RECORDARRAY_H
